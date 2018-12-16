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

#define MethodUsed 7
int main()
{
#if MethodUsed==1
	Mat M(2 ,2 ,CV_8UC3 ,Scalar(0 ,0 ,255 ));
	cout <<M <<endl ;
#elif MethodUsed==2 
	int size[] ={2 ,2 ,2 };
	Mat M(3 ,size ,CV_8UC4 ,Scalar::all(0 )); // A Matrix whose dims is larger than 2 is not expected to be print.
//	cout <<M <<endl ;
#elif MethodUsed==3 
	IplImage* x=cvLoadImage(); // There is no such a function
#elif MethodUsed==4
	Mat M ; // a nul Matrix
	M.create(4 ,4 ,CV_8UC(2) );
	cout <<M <<endl ;
#elif MethodUsed==5
	Mat eyeM =Mat::eye(4 ,4 ,CV_64F );
	cout <<"A eyeM " <<endl <<eyeM <<endl ;
	Mat zeroM =Mat::zeros(5 ,5 ,CV_32F );
	cout <<"A zeroM " <<endl <<zeroM <<endl ;
	Mat oneM =Mat::ones(3 ,3 ,CV_8UC1 );
	cout <<"A oneM" <<endl <<oneM <<endl ;
#elif MethodUsed==6
	Mat M =(Mat_<double>(3 ,3 ) << 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 );
	cout <<M <<endl ;
#else
	Mat M =(Mat_<double>(3 ,3 ) << 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 );
	Mat FirstRow =M.row(0 ).clone();
	cout <<FirstRow <<endl ;
	Mat LastCol =M.col(2 ).clone();
	cout <<LastCol <<endl ;
	
#endif

	system("pause" );
	return 0 ;
}