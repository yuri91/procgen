#pragma once

#include <cheerp/client.h>

namespace client {

class GameState: public Object {
public:
	double get_reward();
	void set_reward(double);
	int get_prev_level_seed();
	void set_prev_level_seed(int);
	int get_level_seed();
	void set_level_seed(int);
	bool get_prev_level_complete();
	void set_prev_level_complete(bool);
	bool get_done();
	void set_done(bool);
	client::HTMLCanvasElement* get_rgb();
	void set_rgb(client::HTMLCanvasElement*);
};

}
