#include "loadinghelper.h"

LoadingHelper loadingHelper;

struct PromiseData
{
	client::Promise* p;
	client::EventListener* f;
	client::EventListener* r;
};

namespace client {
template<typename T>
struct CheerpRef: public Object {
	T* get_inner();
	void set_inner(T*);
};
}

static PromiseData createPromise()
{
	// Create the promise object, store the fullfill callback in a temporary object
	client::Promise* p = nullptr;
	auto* rf = new client::CheerpRef<client::EventListener>();
	auto* rr = new client::CheerpRef<client::EventListener>();
	__asm__("new Promise(function(__f,__r){%1.inner=__f;%2.inner=__r;});" : "=r"(p) : "r"(rf), "r"(rr));
	return PromiseData{p, rf->get_inner(), rr->get_inner()};
}

void LoadingHelper::setRoot(const std::string& root)
{
	this->root = root;
}

client::Promise* LoadingHelper::load(const std::vector<std::string>& images)
{
	int* pending = new int(images.size());
	PromiseData pd = createPromise();
	auto* onLoad = cheerp::Callback([this, pending, f = pd.f](){
		(*pending)--;
		if (*pending != 0)
			return;
		reinterpret_cast<void(*)()>(f)();
	});
	for (const auto& s: images)
	{
		auto* img = static_cast<client::HTMLImageElement*>(client::document.createElement("img"));
		auto it = map.emplace(s, img);
		if (!it.second)
		{
			(*pending)--;
			if (*pending == 0)
				reinterpret_cast<void(*)()>(pd.f)();
			continue;
		}
		auto* src = new client::String(root.c_str());
		src = src->concat(new client::String(s.c_str()));
		img->set_src(src);
		img->set_onload(onLoad);
	}
	return pd.p;
}

client::HTMLImageElement* LoadingHelper::get(const std::string& s)
{
	return map.at(s);
}
