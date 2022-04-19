#include "game-registry.h"

std::map<std::string, std::function<Game*()>> *globalGameRegistry = nullptr;
