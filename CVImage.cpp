#include "CVImage.h"

CVImage::CVImage(const cv::String& filename, int flags)
	: filename{ filename },
	image{ cv::imread(filename, flags) }
{
}

CVImage::CVImage(int rows, int cols, int type)
	: image{ cv::Mat(rows,cols,type) }
{
}

CVImage::CVImage(int rows, int cols, int type, const cv::Scalar& s)
	: image{ cv::Mat(rows,cols,type,s) }
{
}

CVImage::CVImage(const cv::Size& size, int type)
	: image{ size, type }
{
}

CVImage::CVImage(const CVImage& cvImage, const cv::Rect& roi)
	: image{ cvImage.image,roi }
{
}

//CVImage& CVImage::operator=(const cv::Scalar& s)
//{
//	image = s;
//	return *this;
//}

void CVImage::load(const cv::String& filename, int flags)
{
	image = cv::imread(filename, flags);
}

void CVImage::copyTo(const CVImage& target) const
{
	// 如果img指向同一块数据块，则copyTo不会报错
	image.copyTo(target.image);
}

void CVImage::copyTo(const CVImage& target, cv::InputArray mask) const
{
	image.copyTo(target.image, mask);
}

void CVImage::copyTo(const CVImage& target, const CVImage& maskCVImage) const
{
	image.copyTo(target.image, maskCVImage.image);
}

void CVImage::convertTo(CVImage& target, int rtype, double alpha, double beta) const
{
	image.convertTo(target.image, rtype, alpha, beta);
}

int CVImage::channels() const
{
	return image.channels();
}

CVImage CVImage::clone() const
{
	return CVImage{ filename,image.clone() };
}

int CVImage::rows() const
{
	return image.rows;
}

int CVImage::cols() const
{
	return image.cols;
}

void CVImage::resize(cv::Size dsize, double fx, double fy, int interpolation)
{
	cv::resize(image, image, dsize, fx, fy, interpolation);
}

void CVImage::BGR2Gray()
{
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

void CVImage::filp(int flipCode)
{
	flip(image, image, flipCode);
}

void CVImage::flipTo(cv::OutputArray dst, int flipCode) const
{
	flip(image, dst, flipCode);
}

CVImage CVImage::cutROI(const cv::Rect& roi) const
{
	return CVImage{ *this, roi };
}

CVImage CVImage::cutROI(const cv::Range& _rowRange, const cv::Range& _colRange) const
{
	return CVImage{ filename, image(_rowRange, _colRange) };
}

CVImage CVImage::cutRowROI(const cv::Range& r) const
{
	return CVImage{ filename,image.rowRange(r) };
}

CVImage CVImage::cutRowROI(int startrow, int endrow) const
{
	return CVImage{ filename,image.rowRange(startrow,endrow) };
}

CVImage CVImage::cutColROI(const cv::Range& r) const
{
	return CVImage{ filename,image.colRange(r) };
}

CVImage CVImage::cutColROI(int startcol, int endcol) const
{
	return CVImage{ filename,image.colRange(startcol,endcol) };
}

void CVImage::mask(const CVImage& maskCVImage, const cv::Rect& roi)
{
	CVImage imageROI = this->cutROI(roi);
	maskCVImage.copyTo(imageROI);
}

void CVImage::mask(const CVImage& maskCVImage, const cv::Range& _rowRange, const cv::Range& _colRange)
{
	CVImage imageROI = this->cutROI(_rowRange, _colRange);
	maskCVImage.copyTo(imageROI);
}

void CVImage::create(int rows, int cols, int type)
{
	image.create(rows, cols, type);
}

void CVImage::create(const cv::Size& size, int type)
{
	image.create(size, type);
}

void CVImage::circle(cv::Point center, int radius, const cv::Scalar& color, int thickness, int lineType, int shift)
{
	cv::circle(image, center, radius, color, thickness, lineType, shift);
}

void CVImage::putText(const cv::String& text, cv::Point org, int fontFace, double fontScale, cv::Scalar color, int thickness, int lineType, bool bottomLeftOrigin)
{
	cv::putText(image, text, org, fontFace, fontScale, color, thickness, lineType, bottomLeftOrigin);
}

void CVImage::setAllPixels(const cv::Scalar& s)
{
	image = s;
}

void CVImage::show(const cv::String& winname, int delay) const
{
	_insureWindowActive(winname);
	cv::imshow(winname, image);
	cv::waitKey(delay);
}

CVImage::CVImage(const cv::String filename, const cv::Mat image)
	:filename{ filename },
	image{ image }
{
}

void CVImage::_insureWindowActive(const cv::String& winname) const
{
	if (CVWindowMap::getWindow(winname) == nullptr) {
		CVLogger().log(CVLogLevel::FATAL, "No window named ", winname, " was ever created.");
		exit(1);
	}
}