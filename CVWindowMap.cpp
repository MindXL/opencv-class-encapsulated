#include "CVWindowMap.h"

std::unordered_map<cv::String, std::shared_ptr<CVWindow> > CVWindowMap::map;

std::shared_ptr<CVWindow> CVWindowMap::createWindow(const cv::String& winname, int flags)
{
	const auto it = map.find(winname);
	if (it == map.end()) {
		cv::namedWindow(winname, flags);
		// std::shared_ptr<CVWindow> p = std::make_shared<CVWindow>(winname, FindWindow(nullptr, (LPCWSTR)winname.c_str()));
		std::shared_ptr<CVWindow> p = std::make_shared<CVWindow>(winname);
		map.emplace(winname, p);
		return p;
	}
	else return it->second;
}

std::shared_ptr<CVWindow> CVWindowMap::getWindow(const cv::String& winname)
{
	const auto it = map.find(winname);
	return it != map.end() ? it->second : nullptr;
}