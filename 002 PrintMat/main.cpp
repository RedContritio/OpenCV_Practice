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

std::ostream& (*(print[]))(std::ostream& ,const cv::Mat& ) =
{
	[](std::ostream& o ,const cv::Mat& m )->std::ostream&{return o<<m<<endl ;},
	[](std::ostream& o ,const cv::Mat& m )->std::ostream&{return o<<cv::format(m ,cv::Formatter::FMT_PYTHON )<<endl ;},
	[](std::ostream& o ,const cv::Mat& m )->std::ostream&{return o<<cv::format(m ,cv::Formatter::FMT_CSV )<<";"<<endl ;},
	[](std::ostream& o ,const cv::Mat& m )->std::ostream&{return o<<cv::format(m ,cv::Formatter::FMT_NUMPY )<<endl ;},
	[](std::ostream& o ,const cv::Mat& m )->std::ostream&{return o<<cv::format(m ,cv::Formatter::FMT_C )<<endl ;},
};



int main(void )
{
	Mat r(10 ,3 ,CV_8UC3 );
	randu(r ,Scalar::all(0) ,Scalar::all(255) );
	for(int i=0 ;i<sizeof(print )/sizeof(*print ) ;i++ )
	{
		print[i](cout ,r );
		cout <<endl ;
	}
	

	system("pause" );
	return 0 ;
}