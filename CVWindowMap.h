#pragma once

#include <memory>
#include <unordered_map>

#include <opencv2/highgui.hpp>

struct CVWindow {
	cv::String winname;
	// HWND hq;
};

class CVWindowMap
{
	CVWindowMap() = delete;
private:
	static std::unordered_map<cv::String, std::shared_ptr<CVWindow> > map;

public:
	static std::shared_ptr<CVWindow> createWindow(const cv::String& winname, int flags = cv::WINDOW_AUTOSIZE);
	static std::shared_ptr<CVWindow> getWindow(const cv::String& winname);
};
