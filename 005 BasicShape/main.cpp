#include <core.hpp>
#include <core/core_c.h>
#include <core/utility.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>

#include <iostream>
using std::cout ;
using std::endl ;

#include "Binders.hpp"

#define DrawEllipse painter[0]
#define DrawCircle painter[1]
#define DrawLine painter[2]
#define DrawRect painter[3]

void DrawAtom( cv::Mat Img)
{
	for(int i = 0; i < 4; i ++)
	{
		DrawEllipse( Img, cv::Point( Img.cols/2, Img.rows/2),cv::Size( Img.cols/3, Img.rows/6), cv::Scalar::all( 0xFF), i*45);
	}
	DrawCircle( Img, cv::Point( Img.cols/2, Img.rows/2), cv::Size( Img.cols/40, Img.rows/40), cv::Scalar::all( 0xFF), 0, -1);
}

void DrawFractal( cv::Mat Img)
{
	if( Img.rows < 3|| Img.cols < 3)return ;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(( i == 1)!=( j == 1))
			{
				painter[3]( Img, cv::Point( j*Img.cols/3, i*Img.rows/3), cv::Size( Img.cols/3, Img.rows/3), cv::Scalar::all( 0x00), 0, -1);
			}
		}
	}
	DrawFractal( Img.rowRange( Img.rows/3, 2*Img.rows/3).colRange( Img.cols/3, 2*Img.cols/3));
}

int main( void)
{
	cv::Mat Img( 480, 640, CV_8UC4);
	cv::randu( Img, cv::Scalar::all( 0x00), cv::Scalar::all( 0x20));

#if 0
	painter[0]( Img, cv::Point( 80, 100),cv::Size( 100, 50), cv::Scalar( 0xFF, 0xCC, 0x66), 0);
	painter[1]( Img, cv::Point( 200, 400),cv::Size( 100, 50), cv::Scalar( 0x00, 0x00, 0xFF), 0, -1);
	painter[2]( Img, cv::Point( 600, 400),cv::Size( -300, -200), cv::Scalar( 0x00, 0xFF, 0xFF), 0, 2, 4);
#endif
	DrawAtom( Img);
	cv::imshow( "imshow", Img);

	cv::Mat Img2( 480, 640, CV_8UC4);
	cv::randu( Img2, cv::Scalar::all( 0xD0), cv::Scalar::all( 0xFF));
	DrawFractal( Img2);

	cv::imshow( "mat2", Img2);
	cv::waitKey( 0);
	return 0;
}