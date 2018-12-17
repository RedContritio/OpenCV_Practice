#include <core.hpp>
#include <core/core_c.h>
#include <core/utility.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>
using cv::Scalar ;
using cv::Mat ;
using cv::Mat_ ;
using cv::waitKey ;

#include <iostream>
using std::cout ;
using std::endl ;

int main( void)
{
	cv::Point2f p( 2, 3);
	cout<< p<< endl;

	cv::Point3f p1( 4, 5, 6);
	cout<< p1<< endl;

	std::vector< float> vec ;
	vec.push_back( 12);
	vec.push_back( 21.4f);
	vec.push_back( 66.6666f);
	cout<< Mat( vec)<< endl;

	system( "pause");
	return 0;
}