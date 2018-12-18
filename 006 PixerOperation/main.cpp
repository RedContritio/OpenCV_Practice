#include <core.hpp>
#include <core/core_c.h>
#include <core/utility.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>

#include <iostream>
using std::cout ;
using std::endl ;

void ColorSpaceReduce( cv::Mat& img, cv::Size sz)
{
	for(int i=0 ;i<sz.height ;i++ )
	{
		for(int j=0 ;j<sz.width ;j++ )
		{
			cv::Vec3b& rgba =img.at<cv::Vec3b>( i, j);
			rgba[0]^= 0xFF;
			rgba[1]^= 0xFF;
			rgba[2]^= 0xFF;
		}
	}
}

int main( void)
{
	cv::Mat img = cv::imread( "small.png");
	cv::Size sz( img.cols, img.rows);
	printf( "%d %d\n", img.cols, img.rows);
//	cv::resize( img, img, sz);

	ColorSpaceReduce( img, sz);

	cv::imshow( "1", img);
	cv::waitKey( 0);
	return 0;
}