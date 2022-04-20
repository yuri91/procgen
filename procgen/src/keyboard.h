#pragma once

#include <cheerp/client.h>
#include <unordered_map>
#include <string>

class Keyboard {
public:
	Keyboard(client::HTMLElement* div): div(div)
	{
		div->set_onkeydown(cheerp::Callback([this](client::KeyboardEvent* ev)
		{
			state[std::string(*ev->get_code())] = true;
		}));
		div->set_onkeyup(cheerp::Callback([this](client::KeyboardEvent* ev)
		{
			state[std::string(*ev->get_code())] = false;
		}));
	}
	bool isDown(const char* key)
	{
		return state[key];
	}
	~Keyboard()
	{
		div->set_onkeydown(nullptr);
		div->set_onkeyup(nullptr);
	}
private:
	std::unordered_map<std::string, bool> state;
	client::HTMLElement* div;
};
