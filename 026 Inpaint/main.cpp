#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <photo.hpp>

#include "_imgproc.h"
#include "_scroll.h"

using cv::Mat;

void onMouse(int event, int x, int y, int flags, void* userdata);

int Scroll_Variable(radius, 30, 0, 30, 0);
int Scroll_Variable(Penwidth, 10, 1, 9, 1);

Mat mask, img_;
inline void ApplyInpaint(Mat& src, Mat& mask, int radius)
{
	Mat inpainted;
	cv::inpaint(src, mask, inpainted, radius, cv::INPAINT_TELEA);
	_imshow(inpainted);
}

int main(void)
{
	Mat img = cv::imread("1.jpg");
	_resize(img, /3);
	img_ = img.clone();
	mask = cv::Mat::zeros(img.size(), CV_8UC1);
	_imshow(img);
	_imshow(img_);
	cv::setMouseCallback("img_", onMouse, &img);
	Scroll_add(radius, "img_", &img);
	Scroll_add(Penwidth, "img_", &img);

	cv::waitKey();
	return 0;
}


void onMouse(int event, int x, int y, int flags, void* userdata)
{
	static cv::Point point0;
	if(!__LIMIT_POSITION(img_, x, y)) return;
	if(event == cv::EVENT_RBUTTONDOWN)
	{
		ApplyInpaint(img_, mask, Scroll_value(radius));
	}
	if(event == cv::EVENT_MOUSEWHEEL)
	{
		mask = cv::Scalar::all(0);
		img_ = ((Mat*)userdata)->clone();
	}
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		point0 = cv::Point(x, y);
	}
	else if(event == cv::EVENT_MOUSEMOVE&& (flags&cv::EVENT_LBUTTONDOWN))
	{
		cv::Point point1(x, y);
		cv::line(mask, point0, point1, cv::Scalar::all(255), Scroll_value(Penwidth));
		cv::line(img_, point0, point1, cv::Scalar::all(255), Scroll_value(Penwidth));
		point0 = point1;
	}
	_imshow(img_);
}

void onScroll(int pos, void* userdata)
{
	//ApplyInpaint(img_, mask, Scroll_value(radius));
}