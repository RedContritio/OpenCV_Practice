#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "_imgproc.h"

void onMouse(int event, int x, int y, int flags, void* userdata);

int main(void)
{
	cv::Mat backimg = cv::imread("0.jpg");
	MatResize(backimg, *1/2);
	// 202 77 302 257 is ROI
	//cv::Mat frontimg = cv::imread("1.jpg");
	//MatResize(frontimg, *1/2);
	cv::imshow("back", backimg);
	cv::Mat dst/*(backimg.size(), backimg.type())*/;
	cv::Mat map_x(backimg.size(), CV_32FC1), map_y(backimg.size(), CV_32FC1);
	for(int i = 0; i < backimg.rows; ++i)
	{
		for(int j = 0; j < backimg.cols; ++j)
		{
			map_x.at<float>(i, j) = static_cast<float>(2*j);
			map_y.at<float>(i, j) = static_cast<float>(i);
		}
	}
	cv::remap(backimg, dst, map_x, map_y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("dst", dst);
	//cv::setMouseCallback("back", onMouse, &backimg);
	//cv::imshow("front", frontimg);
	cv::waitKey();
	return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	static int lx = 0, ly = 0, rx = 0, ry = 0;
	switch(event)
	{
		case cv::EVENT_LBUTTONDOWN:
		{
			printf("L %d %d\n", lx, ly);
			lx = x;
			ly = y;
			break;
		};
		case cv::EVENT_RBUTTONDOWN:
		{
			printf("R %d %d\n", rx, ry);
			rx = x;
			ry = y;
			break;
		};
		default:
			return ;
			break;
	}
	cv::Mat& src = *(cv::Mat*)userdata;
	if( rx > lx && ry > ly)
	{
		printf("us\n");
		cv::Mat dst = src.clone();
		cv::rectangle(dst, cv::Point(lx, ly), cv::Point(rx, ry), cv::Scalar(0,0,0), -1);
		cv::imshow("back", dst);
	}
	else
	{
		cv::imshow("back", src);
	}
}