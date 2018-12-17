#include <core.hpp>
#include <core/core_c.h>
#include <core/utility.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>

#include <iostream>
using std::cout ;
using std::endl ;

int main( void)
{
#if 0
	cv::Mat M( 480, 640, CV_8UC4, cv::Scalar(0xFF, 0xCC, 0x66));
	cv::imshow( "M", M);

	cv::Rect rec( 20, 40, 640, 480);
	cv::Rect rec2( 50, 60, 640, 480);
	rec |= rec2 ;
	cout<< rec<< endl;
#endif
	cv::Mat SrcPic =cv::imread( "pic.png", 1);
	cv::imshow( "Src", SrcPic);
	cv::Mat DstPic ;
	cv::cvtColor( SrcPic, DstPic, cv::COLOR_RGB2Lab);
	cv::imshow( "Dst", DstPic);
	cv::Mat Dst1Pic ;
	cv::cvtColor( SrcPic, Dst1Pic, cv::COLOR_RGB2GRAY);
	cv::imshow( "Dst1", Dst1Pic);
	cv::waitKey(0 );
	return 0;
}