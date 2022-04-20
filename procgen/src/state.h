#pragma once

#include <cheerp/client.h>

struct GameState {
	double reward;
	int prev_level_seed;
	int level_seed;
	bool prev_level_complete;
	bool done;
};
