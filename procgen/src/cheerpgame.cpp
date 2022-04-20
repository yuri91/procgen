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
		game->action = getAction();
		game->step();
		game->observe();
		totalReward+= state.reward;
		displayState();
		kb->clear();
	}
	void displayState()
	{
		std::string hud = std::string("Reward: ") + std::to_string(state.reward) + "\n" +
			"Total reward: " + std::to_string(totalReward) + "\n" +
			"Level seed: " + std::to_string(state.level_seed) + "\n" +
			"Previous level seed: " + std::to_string(state.prev_level_seed) + "\n" +
			"Previous level complete: " + std::to_string(state.prev_level_complete) + "\n" +
			"Done: " + std::to_string(state.done) + "\n";
		stateDiv->set_innerText(hud.c_str());
	}
	void destroy()
	{
		delete kb;
		kb = nullptr;
		delete game;
		game = nullptr;
	}
	static client::Promise* init(client::String* name, client::CheerpGameOpts* opts)
	{
		auto* p = images_load();
		return p->then(cheerp::Callback([name, opts](){
			return new CheerpGame(name, opts);
		}));
	}

private:
	CheerpGame(client::String* jsname, client::CheerpGameOpts* opts)
	{
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

		game->state = &state;
		game->level_seed_rand_gen.seed(opts->get_seed());
		game->options.use_generated_assets = false;
		game->game_init();
		game->reset();
		game->observe();
		game->initial_reset_complete = true;

		stateDiv = client::document.createElement("div");
		div->appendChild(stateDiv);

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
				if (!kb->isPressed(k))
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
	GameState state;
	double totalReward{0};
	client::HTMLElement* stateDiv;
	client::HTMLCanvasElement* canvas;
};
