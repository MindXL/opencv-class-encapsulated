#include <string>
#include <opencv2/opencv.hpp>

#include "CVImage.h"
#include "CVWindowMap.h"
#include "CVLogger.h"

int _main() {
	CVLogger logger;
	logger.setLogLevel(CVLogLevel::FATAL);

	std::string filename{ "" };
	CVImage image(filename);

	std::string winname{ "Image" };

	CVWindowMap::createWindow(winname);

	image.show(winname);

	return 0;
}