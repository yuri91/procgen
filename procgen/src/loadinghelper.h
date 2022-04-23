#pragma once

#include <cheerp/client.h>
#include <vector>
#include <string>
#include <unordered_map>

class LoadingHelper {
public:
	void setRoot(const std::string& root);
	client::Promise* load(const std::vector<std::string>& images);
	client::HTMLImageElement* get(const std::string& s);
private:
	std::unordered_map<std::string, client::HTMLImageElement*> map;
	std::string root;
};

extern LoadingHelper loadingHelper;
