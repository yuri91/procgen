#include <cheerp/client.h>
#include "game-registry.h"
#include "game.h"
#include "resources.h"

namespace client {
	class CheerpGameOpts: public Object {
	public:
		int get_seed();
	};
}

class [[cheerp::jsexport]] CheerpGame {
public:
	void step()
	{
		game->step();
	}
	void destroy()
	{
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
		canvas = static_cast<client::HTMLCanvasElement*>(client::document.createElement("canvas"));
		canvas->set_width(RENDER_RES);
		canvas->set_height(RENDER_RES);
		auto* style = canvas->get_style();

		game->set_canvas(canvas);
		div->appendChild(canvas);

		game->level_seed_rand_gen.seed(opts->get_seed());
		game->options.use_generated_assets = false;
		game->game_init();
		game->reset();
		game->observe();
		game->initial_reset_complete = true;
		step();
	}

	Game* game;
	client::HTMLCanvasElement* canvas;
};
