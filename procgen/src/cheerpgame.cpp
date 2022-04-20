#include <cheerp/client.h>
#include "game-registry.h"
#include "game.h"
#include "resources.h"
#include "state.h"
#include "keyboard.h"

namespace client {
	class CheerpGameOpts: public Object {
	public:
		int get_seed();
	};
}

std::vector<std::vector<const char*>> combos =
{
	{"ArrowLeft", "ArrowDown"},
	{"ArrowLeft",},
	{"ArrowLeft", "ArrowUp"},
	{"ArrowDown",},
	{},
	{"ArrowUp",},
	{"ArrowRight", "ArrowDown"},
	{"ArrowRight",},
	{"ArrowRight", "ArrowUp"},
	{"KeyD",},
	{"KeyA",},
	{"KeyW",},
	{"KeyS",},
	{"KeyQ",},
	{"KeyE",},
};

class [[cheerp::jsexport]] CheerpGame {
public:
	void step()
	{
		int action = getAction();
		client::console.log("step", action);
		state->set_action(action);
		game->action = action;
		game->step();
		game->observe();
	}
	void destroy()
	{
		delete kb;
		kb = nullptr;
		delete game;
		game = nullptr;
	}
	static client::Promise* init(client::String* name, client::CheerpGameOpts* opts, client::GameState* state)
	{
		auto* p = images_load();
		return p->then(cheerp::Callback([name, opts, state](){
			return new CheerpGame(name, opts, state);
		}));
	}

private:
	CheerpGame(client::String* jsname, client::CheerpGameOpts* opts, client::GameState* state)
	{
		this->state = state;
		std::string name(*jsname);
		game = globalGameRegistry->at(name)();
		auto* div = client::document.getElementById("app");
		kb = new Keyboard(client::document.get_body());
		canvas = static_cast<client::HTMLCanvasElement*>(client::document.createElement("canvas"));
		canvas->set_width(RENDER_RES);
		canvas->set_height(RENDER_RES);
		auto* style = canvas->get_style();

		game->set_canvas(canvas);
		div->appendChild(canvas);

		game->state = state;
		game->level_seed_rand_gen.seed(opts->get_seed());
		game->options.use_generated_assets = false;
		game->game_init();
		game->reset();
		game->observe();
		game->initial_reset_complete = true;
		step();

		client::setInterval(cheerp::Callback([this]()
		{
			step();
		}), 100);
	}

	int getAction()
	{
		int longest = -1;
		int action = -1;
		int i = 0;
		for (auto& combo: combos)
		{
			bool hit = true;
			for (auto* k: combo)
			{
				if (!kb->isDown(k))
				{
					hit = false;
					break;
				}
			}
			if (hit && longest < (int)combo.size())
			{
				longest = combo.size();
				action = i;
			}
			i++;
		}
		return action;
	}

	Game* game;
	Keyboard* kb;
	client::GameState* state;
	client::HTMLCanvasElement* canvas;
};
