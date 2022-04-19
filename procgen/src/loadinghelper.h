#pragma once

#include <cheerp/client.h>
#include <vector>
#include <string>
#include <unordered_map>

class LoadingHelper {
public:
	client::Promise* load(const std::vector<std::string>& images);
	client::HTMLImageElement* get(const std::string& s);
private:
	std::unordered_map<std::string, client::HTMLImageElement*> map;
};

extern LoadingHelper loadingHelper;
