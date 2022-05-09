#include "../basic-abstract-game.h"
#include "../mazegen.h"

const std::string NAME = "maze";

const float REWARD = 10.0;

const int GOAL = 2;

const int EASY_GRID_SIZE = 15;
const int HARD_GRID_SIZE = 25;
const int MEMORY_GRID_SIZE = 31;

class MazeGame : public BasicAbstractGame {
  public:
    std::shared_ptr<MazeGen> maze_gen;
    int maze_dim = 0;
    int world_dim = 0;

    MazeGame()
        : BasicAbstractGame(NAME) {
        timeout = 500;
        random_agent_start = false;
        has_useful_vel_info = false;

        out_of_bounds_object = WALL_OBJ;
        visibility = 8.0;
    }

    void load_background_images() override {
        main_bg_images_ptr = &topdown_backgrounds;
    }

    void asset_for_type(int type, std::vector<std::string> &names) override {
        if (type == WALL_OBJ) {
            names.push_back("kenney/Ground/Sand/sandCenter.png");
        } else if (type == GOAL) {
            names.push_back("misc_assets/cheese.png");
        } else if (type == PLAYER) {
            names.push_back("kenney/Enemies/mouse_move.png");
        }
    }

    void choose_world_dim() override {
        int dist_diff = options.distribution_mode;

        if (dist_diff == EasyMode) {
            world_dim = EASY_GRID_SIZE;
        } else if (dist_diff == HardMode) {
            world_dim = HARD_GRID_SIZE;
        } else if (dist_diff == MemoryMode) {
            world_dim = MEMORY_GRID_SIZE;
        }

        main_width = world_dim;
        main_height = world_dim;
    }

    void game_reset() override {
        BasicAbstractGame::game_reset();

        grid_step = true;

        maze_dim = rand_gen.randn((world_dim - 1) / 2) * 2 + 3;
        int margin = (world_dim - maze_dim) / 2;

        std::shared_ptr<MazeGen> _maze_gen(new MazeGen(&rand_gen, maze_dim));
        maze_gen = _maze_gen;

        options.center_agent = options.distribution_mode == MemoryMode;

        agent->rx = .5;
        agent->ry = .5;
        agent->x = margin + .5;
        agent->y = margin + .5;

        maze_gen->generate_maze();
        maze_gen->place_objects(GOAL, 1);

        // Fill top row with walls
        for (int i = 0; i < grid_size; i++) {
            set_obj(i, WALL_OBJ);
        }

        // Move maze_gen grid to grid with offset
        for (int i = 0; i < maze_dim; i++) {
            for (int j = 0; j < maze_dim; j++) {
                int type = maze_gen->grid.get(i + MAZE_OFFSET, j + MAZE_OFFSET);

                set_obj(margin + i, margin + j, type);
            }
        }

        // Fill other rows with walls
        if (margin > 0) {
            for (int i = 0; i < maze_dim + 2; i++) {
                set_obj(margin - 1, margin + i - 1, WALL_OBJ);
                set_obj(margin + maze_dim, margin + i - 1, WALL_OBJ);

                set_obj(margin + i - 1, margin - 1, WALL_OBJ);
                set_obj(margin + i - 1, margin + maze_dim, WALL_OBJ);
            }
        }
    }

    void set_action_xy(int move_action) override {
        BasicAbstractGame::set_action_xy(move_action);
        if (action_vx != 0)
            action_vy = 0;
    }

    void game_step() override {
        BasicAbstractGame::game_step();

        if (action_vx > 0)
            agent->is_reflected = true;
        if (action_vx < 0)
            agent->is_reflected = false;

        int ix = int(agent->x);
        int iy = int(agent->y);

        if (get_obj(ix, iy) == GOAL) {
            set_obj(ix, iy, SPACE);
            step_data.reward += REWARD;
            step_data.level_complete = true;
        }

        step_data.done = step_data.reward > 0;
    }

    void serialize(WriteBuffer *b) override {
        BasicAbstractGame::serialize(b);
        b->write_int(maze_dim);
        b->write_int(world_dim);
    }

    void deserialize(ReadBuffer *b) override {
        BasicAbstractGame::deserialize(b);
        maze_dim = b->read_int();
        world_dim = b->read_int();
    }

    struct MazeState {
        int grid_width;
        int grid_height;
        std::vector<int> grid;
        int agent_x;
        int agent_y;
    };

    MazeState
    get_latent_state() {
        MazeState state;
        Grid<int> grid = get_grid();

        state.grid_width = grid.w;
        state.grid_height = grid.h;
        state.grid = grid.data;

        state.agent_x = agent->x;
        state.agent_y = agent->y;

        return state;
    }

    void observe() override {
        Game::observe();

        auto latent_state = get_latent_state();

        auto* js_state = static_cast<client::MazeState*>(this->state);

        js_state->set_grid_width(latent_state.grid_width);
        js_state->set_grid_height(latent_state.grid_height);

        int32_t grid_size = latent_state.grid_width*latent_state.grid_height;
        int32_t* grid = new int32_t[grid_size];
        auto grid_start = latent_state.grid.begin();
        auto grid_stop = latent_state.grid.begin();
        std::advance(grid_stop, grid_size);
        std::copy(grid_start, grid_stop, grid);
        js_state->set_grid(cheerp::MakeTypedArray(grid, grid_size));

        js_state->set_agent_x(latent_state.agent_x);
        js_state->set_agent_y(latent_state.agent_y);

    }
};

REGISTER_GAME(NAME, MazeGame);
