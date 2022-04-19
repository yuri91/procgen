#pragma once

#include <cheerp/client.h>

namespace client {

class Info: public Object {
public:
	void set_prev_level_seed(int);
	void set_level_seed(int);
	void set_prev_level_complete(bool);
};

class GameState: public Object {
public:
	int get_action();
	void set_info(Info*);
	void set_reward(double);
	void set_done(bool);
};
}
