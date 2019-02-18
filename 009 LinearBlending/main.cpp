#include <core/core.hpp>
#include <highgui/highgui.hpp>

#include "LinearMixer.h"

template<int> struct Printer;
int main( void)
{
	cv::Mat img1 = cv::imread("1.png");
	cv::Mat img2 = cv::imread("2.png");
	cv::imshow( "img1", img1);
	cv::imshow( "img2", img2);
	
	cv::Mat dst;
	LinearMix(img1, img2, dst, 1, 1);
	cv::imshow( "dst", dst);
	cv::waitKey();
	return 0;
}