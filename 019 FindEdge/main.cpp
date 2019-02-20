#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "_imgproc.h"

int main(void)
{
	cv::Mat img = cv::imread("1.jpg", 1);
	printf("%d %d\n",img.elemSize(), sizeof(cv::Vec3b));
	
	cv::imshow("s", img);
	cv::Mat dst;
	//cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
	//cv::imshow("g", img);
	//cv::morphologyEx(img, img, cv::MORPH_ERODE,cv::getStructuringElement(cv::MORPH_RECT, cv::Size(11, 11)));
	//cv::imshow("er", img);
	//cv::morphologyEx(img, img, cv::MORPH_BLACKHAT,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11)));
	//cv::imshow("bh", img);
	cv::Canny(img, dst, 3, 9, 3);
	cv::imshow("", dst);
	RedContritio::Experiment::inverseColor<uchar,1>(dst, dst);
	cv::imshow("rev", dst);
	cv::imwrite("3.jpg", dst);
	cv::waitKey();
	return 0;
}