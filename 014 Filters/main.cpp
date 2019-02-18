#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include "MatResize.h"
#include "imgproc_.h"

#include <cstdlib>
#include <ctime>

void BlurTest(cv::Mat& img);

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	cv::Mat img = cv::imread("1.jpg");

	MatResize(img, *2/3);

	cv::imshow("",img);

	//BlurTest(img);
	cv::Mat dst;
	RedContritio::Experiment::salt(img, dst, 0.3);
	cv::imshow( "salt", dst);

	BlurTest(dst);

	cv::waitKey();
	return 0;
}



void BlurTest(cv::Mat& img)
{
	cv::Mat dst, dst2;
	cv::blur(img, dst, cv::Size(10, 10));
	cv::imshow("dst", dst);
	return ;

	// I do not want to run it 
	RedContritio::Experiment::blur(img, dst2, cv::Size(10, 10)); // As we all know, function in RedContritio is slow and filled with bugs
	cv::imshow("dst2", dst2);
	return ;
}