#pragma once

#include <cheerp/client.h>
#include <unordered_set>
#include <string>

class Keyboard {
public:
	Keyboard(client::HTMLElement* div): div(div)
	{
		div->set_onkeydown(cheerp::Callback([this](client::KeyboardEvent* ev)
		{
			state.insert(std::string(*ev->get_code()));
		}));
	}
	bool isPressed(const char* key)
	{
		return state.count(key) != 0;
	}
	void clear()
	{
		state.clear();
	}
	~Keyboard()
	{
		div->set_onkeydown(nullptr);
	}
private:
	std::unordered_set<std::string> state;
	client::HTMLElement* div;
};
