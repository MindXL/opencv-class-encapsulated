#pragma once

#include <iostream>
#include <string>
#include <list>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

#include "CVWindowMap.h"
#include "CVLogger.h"

class CVImage
{
private:
	cv::String filename;
	cv::Mat image;

public:
	CVImage() = default;
	CVImage(const cv::String& filename, int flags = cv::IMREAD_COLOR);
	CVImage(int rows, int cols, int type);
	CVImage(int rows, int cols, int type, const cv::Scalar& s);
	CVImage(const cv::Size& size, int type);

	/// <summary>
	/// 根据cvImage获取一个ROI信息
	/// CVImage imageROI{ cvImage, roi };
	/// </summary>
	/// <param name="cvImage"></param>
	/// <param name="roi"></param>
	CVImage(const CVImage& cvImage, const cv::Rect& roi);

	// CVImage& operator = (const cv::Scalar& s);

	/* load */
	CVImage(const CVImage&) = default;
	inline CVImage& operator = (const CVImage&) = default;
	/// <summary>
	///
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="flags">cv::ImreadModes</param>
	void load(const cv::String& filename, int flags = cv::IMREAD_COLOR);

	/* copy */
	/// <summary>
	/// 复制一份内容至dst
	/// src.copyTo(dst);
	/// </summary>
	/// <param name="target"></param>
	void copyTo(const CVImage& target) const;
	void copyTo(const CVImage& target, cv::InputArray mask) const;
	void copyTo(const CVImage& target, const CVImage& maskCVImage) const;
	/// <summary>
	/// 将内容转换至dst
	/// src.convertTo(dst);
	/// </summary>
	/// <param name="target"></param>
	/// <param name="rtype"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	void convertTo(CVImage& target, int rtype, double alpha = 1.0, double beta = 0.0) const;

	/* properties */
	/// <summary>
	///
	/// </summary>
	/// <returns>图像的通道数</returns>
	int channels() const;
	/// <summary>
	///
	/// </summary>
	/// <returns>图像的副本</returns>
	CVImage clone() const;
	/// <summary>
	///
	/// </summary>
	/// <returns>图像的行数</returns>
	int rows() const;
	/// <summary>
	///
	/// </summary>
	/// <returns>图像的列数</returns>
	int cols() const;

	/* judges */

	/* operate */
	/// <summary>
	/// 重设图像大小
	/// </summary>
	/// <param name="dsize"></param>
	/// <param name="fx"></param>
	/// <param name="fy"></param>
	/// <param name="interpolation">cv::InterpolationFlags</param>
	void resize(cv::Size dsize, double fx = 0, double fy = 0,
		int interpolation = cv::INTER_LINEAR);
	/// <summary>
	/// 将彩色图像转换为灰度图
	/// </summary>
	void BGR2Gray();
	// void ToBinary();
	/// <summary>
	/// 翻转图像
	/// </summary>
	/// <param name="flipCode"></param>
	void filp(int flipCode);
	/// <summary>
	/// 翻转图像至dst
	/// src.flipTo(dst [, flipCode]);
	/// </summary>
	/// <param name="dst"></param>
	/// <param name="flipCode"></param>
	void flipTo(cv::OutputArray dst, int flipCode) const;
	/// <summary>
	/// CVImage imageROI = cvImage.cutROI(
	///     {
	///         image.cols() - logo.cols(),
	///         image.rows() - logo.rows(),
	///         logo.cols(), logo.rows()
	///     }
	/// );
	/// </summary>
	/// <param name="roi"></param>
	/// <returns></returns>
	CVImage cutROI(const cv::Rect& roi) const;
	/// <summary>
	/// CVImage imageROI = cvImage.cutROI(
	///     { image.rows() - logo.rows(), image.rows() },
	///     { image.cols() - logo.cols(), image.cols() }
	/// );
	/// </summary>
	/// <param name="roi"></param>
	/// <returns></returns>
	CVImage cutROI(const cv::Range& _rowRange, const cv::Range& _colRange) const;

	/// <summary>
	/// CVImage rowROI = cvImage.cutRowROI({startrow, endrow});
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	CVImage cutRowROI(const cv::Range& r) const;
	/// <summary>
	/// CVImage rowROI = cvImage.cutRowROI(startrow, endrow);
	/// </summary>
	/// <param name="startrow"></param>
	/// <param name="endrow"></param>
	/// <returns></returns>
	CVImage cutRowROI(int startrow, int endrow) const;
	/// <summary>
	/// CVImage colROI = cvImage.cutColROI({startcol, endcol});
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	CVImage cutColROI(const cv::Range& r) const;
	/// <summary>
	/// CVImage colROI = cvImage.cutColROI(startcol, endcol);
	/// </summary>
	/// <param name="startcol"></param>
	/// <param name="endcol"></param>
	/// <returns></returns>
	CVImage cutColROI(int startcol, int endcol) const;
	void mask(const CVImage& maskCVImage, const cv::Rect& roi);
	void mask(const CVImage& maskCVImage, const cv::Range& _rowRange, const cv::Range& _colRange);

	/* access */
	template<typename _Tp>
	_Tp& at(int i0, int i1);

	/* draw */
	void create(int rows, int cols, int type);
	void create(const cv::Size& size, int type);
	void circle(cv::Point center, int radius,
		const cv::Scalar& color, int thickness = 1,
		int lineType = cv::LineTypes::LINE_8, int shift = 0);
	void putText(const cv::String& text, cv::Point org,
		int fontFace, double fontScale, cv::Scalar color,
		int thickness = 1, int lineType = cv::LineTypes::LINE_8,
		bool bottomLeftOrigin = false);
	void setAllPixels(const cv::Scalar& s);

	/* onMouse events */
	/// <summary>
	/// 鼠标左键单击窗体时在终端输出该像素点的值
	/// </summary>
	/// <param name="winname"></param>
	template<typename _Tp>
	void showPointOnMouseClick(const cv::String& winname);

	/* display */
	/// <summary>
	/// Make sure the target window is created before this method is called.
	/// </summary>
	/// <param name="winname"></param>
	/// <param name="delay"></param>
	void show(const cv::String& winname, int delay = 0) const;

private:
	CVImage(const cv::String filename, const cv::Mat image);

	// log
	void _insureWindowActive(const cv::String& winname) const;
};

template<typename _Tp>
inline _Tp& CVImage::at(int i0, int i1)
{
	return image.at<_Tp>(i0, i1);
}

template<typename _Tp>
inline void CVImage::showPointOnMouseClick(const cv::String& winname)
{
	_insureWindowActive(winname);
	cv::setMouseCallback(
		winname,
		[](int event, int x, int y, int flags, void* param) {
			decltype(image)* p = reinterpret_cast<decltype(image)*>(param);
			if (event == CV_EVENT_LBUTTONDOWN) {
				std::cout << '(' << x << ", " << y << ") = " << p->at<_Tp>(cv::Point(x, y)) << std::endl;
			}
		},
		reinterpret_cast<void*>(&image)
			);
}
