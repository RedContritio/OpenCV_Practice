#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "MatResize.h"
#include "imgproc_.h"

#include <cstdio>
#include <iostream>

int tolerance = 20;
void on_mouse(int event, int x, int y, int flags, void *ustc);
void onScroll(int pos, void* userdata);

int main(void)
{
	cv::Mat img = cv::imread("1.jpg");
	MatResize(img, *1/2);
	
	cv::imshow("img", img);
	cv::setMouseCallback("img", on_mouse, &img);

	cv::createTrackbar("Tolerance", "img", &tolerance, 255, onScroll);

	cv::waitKey();
	return 0;
}


void on_mouse(int event, int x, int y, int flags, void *ustc)
{
	cv::Mat& img = *(cv::Mat*)ustc;
	switch (event)
	{
		case 1: //cv::CV_EVENT_LBUTTONDOWN:
		{
			std::cout<< x<< ' '<< y<< ' '<< img.at<cv::Vec3b>(y, x)<< std::endl;
			cv::Mat dst = img.clone();
			cv::Scalar dif(tolerance, tolerance, tolerance);
			cv::floodFill(dst, cv::Point(x, y), cv::Scalar(0), 0, dif, dif, 4|cv::FLOODFILL_FIXED_RANGE);
			cv::imshow("img", dst);

			cv::Mat dst2 = img.clone();
			RedContritio::Experiment::floodFill(dst2, cv::Point(x, y), cv::Scalar(0), 0, dif, dif, 4|cv::FLOODFILL_FIXED_RANGE);
			cv::imshow("img2", dst2);

			printf("is same ? %s\n",RedContritio::Experiment::operator==(dst, dst2)?"yes":"no");
			break;
		}
		default:
			break;
	};
}

void onScroll(int pos, void* userdata)
{
	;
}