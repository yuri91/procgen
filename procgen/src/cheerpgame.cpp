#include <cheerp/client.h>
#include "game-registry.h"
#include "game.h"

namespace client {
	class CheerpGameOpts: public Object {
	public:
		int get_seed();
	};
}

class [[cheerp::jsexport]] CheerpGame {
public:
	CheerpGame(client::String* jsname, client::CheerpGameOpts* opts)
	{
		std::string name(*jsname);
		game = globalGameRegistry->at(name)();
		auto* div = client::document.getElementById("app");
		canvas = static_cast<client::HTMLCanvasElement*>(client::document.createElement("canvas"));
		canvas->set_width(RES_W);
		canvas->set_height(RES_H);
		auto* style = canvas->get_style();

		game->set_canvas(canvas);
		div->appendChild(canvas);

		game->level_seed_rand_gen.seed(opts->get_seed());
		game->options.use_generated_assets = true;
		game->game_init();
		game->reset();
		game->observe();
		game->initial_reset_complete = true;
		step();
	}
	void step()
	{
		game->step();
	}
	void destroy()
	{
		delete game;
		game = nullptr;
	}

private:
	Game* game;
	client::HTMLCanvasElement* canvas;
};
