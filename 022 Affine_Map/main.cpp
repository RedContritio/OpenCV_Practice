#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "_imgproc.h"

using cv::Mat;

#define Scroll_Variable(name, all, count, init) name##_step = all/count, name##_count = count; int name = init;
#define Scroll_adjust(name, all, count) name##_step = all/count, name##_count = count;
#define Scroll_add(name, winname, usrdata) cv::createTrackbar(#name, winname, &name, name##_count, onScroll, usrdata);
#define Scroll_value(name) (name* name##_step)

int Scroll_Variable(dx, 1000, 10, 0);
int Scroll_Variable(dy, 1000, 10, 0);
int Scroll_Variable(angle, 360, 360, 0);
double Scroll_Variable(scale, 2.0, 40, 20);
int Scroll_Variable(cx, 1000, 10, 0);
int Scroll_Variable(cy, 1000, 10, 0);

void onScroll(int pos, void* userdata);
int main(void)
{
	Mat src = cv::imread("1.jpg");
	MatResize(src, /2);
	cv::imshow("", src);
	Scroll_adjust(dx, src.cols, 128);
	Scroll_adjust(dy, src.rows, 128);
	Scroll_adjust(cx, src.cols, 128);
	Scroll_adjust(cy, src.rows, 128);
	cv::namedWindow("holder");
	cv::resizeWindow("holder", cv::Size(src.cols, 400));
	Scroll_add(dx, "holder", &src);
	Scroll_add(dy, "holder", &src);
	Scroll_add(angle, "holder", &src);
	Scroll_add(scale, "holder", &src);
	Scroll_add(cx, "holder", &src);
	Scroll_add(cy, "holder", &src);
	cv::waitKey();
	return 0;
}

#define Deg2Rad(theta) ((theta)*CV_PI/180)

void onScroll(int pos, void* userdata)
{
	Mat& src = *(Mat*)userdata;
	Mat dst, warpMatrix(2, 3, CV_32FC1, cv::Scalar(0));
	double c = cos(Deg2Rad(Scroll_value(angle)));
	double s = sin(Deg2Rad(Scroll_value(angle)));
	int svcx = -Scroll_value(cx);
	int svcy = -Scroll_value(cy);
	warpMatrix = (cv::Mat_<float>(2,3) << 
		Scroll_value(scale)* c, Scroll_value(scale)* -s, (svcx* c- svcy* s- svcx)+ Scroll_value(dx),
		Scroll_value(scale)* s, Scroll_value(scale)*  c, (svcx* s+ svcy* c- svcy)+ Scroll_value(dy));
	// What a fuck matrix !!!!!!!!
	cv::warpAffine(src, dst, warpMatrix, src.size());
	cv::imshow("dst_", dst);
}