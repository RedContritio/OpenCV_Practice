#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include "ColorReduce.h"
int main( void)
{
	cv::Mat img = cv::imread( "small.png");

	cv::Mat dst ;
	ColorReduce( img, dst);
	
	cv::imshow( "src", img);
	cv::imshow( "dst", dst);
	cv::waitKey( 0);
}