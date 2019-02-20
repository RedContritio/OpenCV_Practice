#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "MatResize.h"
#include "_imgproc.h"

int thresholdValue, thresholdMaxValue = 255, selctMethod = 0;
void onScroll(int pos, void* userdata);

int main(void)
{
	cv::Mat img = cv::imread("1.jpg");
	MatResize(img, *1/2);
	cv::namedWindow("holder");
	
	//cv::imshow("threshold op", img);
	cv::createTrackbar("Threshold", "holder", &thresholdValue, 255, onScroll, &img);
	cv::createTrackbar("maxv", "holder", &thresholdMaxValue, 255, onScroll, &img);
	cv::createTrackbar("method", "holder", &selctMethod, 4, onScroll, &img);

	cv::waitKey();
	return 0;
}

void onScroll(int pos, void* userdata)
{
	cv::Mat& img = *(cv::Mat*)userdata;
	cv::Mat dst, dst2;
	cv::threshold(img, dst, thresholdValue, thresholdMaxValue, selctMethod);
	RedContritio::Experiment::threshold(img, dst2, thresholdValue, thresholdMaxValue, selctMethod);
	cv::imshow("threshold op", dst);
	cv::imshow("threshold reco", dst2);
}