#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <vector>

#include "_imgproc.h"
#include "_scroll.h"

using cv::Mat;
using cv::imread;
using cv::imshow;
using cv::waitKey;

using std::vector;

int Scroll_Variable(thre, 255, 255, 0);

vector<vector<cv::Point>> contours;
vector<cv::Vec4i> hierarchy;
vector<Mat> hullsMatrix( 256);

int main()
{
	::srand(::time(0));
	Mat img = imread("1.jpg");
	_resize(img, /3);

	cv::namedWindow("img");

	cv::resizeWindow("img", cv::Size(864, 60));
	
	for(int i=0; i<256; ++i)
	{
		Mat t;
		cv::cvtColor(img, t, cv::COLOR_RGB2GRAY);
		cv::threshold(t, t, i, 255, cv::THRESH_BINARY);
		_imshow(t);
		vector<vector<cv::Point>> contours;
		vector<cv::Vec4i> hierarchy;
		cv::findContours(t, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
		vector<vector<cv::Point>> hulls(contours.size());
		for(int j = 0; j < contours.size(); ++j)
		{
			cv::convexHull( contours[j], hulls[j]);
		}
		Mat dst = Mat::zeros(img.size(), CV_8UC3);
		for(int j = 0; j < contours.size(); ++j)
		{
			cv::drawContours(dst, contours, j, cv::Scalar(255, 0, 0));
			cv::drawContours(dst, hulls, j, cv::Scalar(0, 255, 0));
		}
		hullsMatrix[i] = dst;
		if(i%0x10==0)printf("%x\n",i);
	}

	Scroll_add(thre, "img", &img)



	waitKey();
	return 0;
}

void onScroll(int pos, void* userdata)
{
	Mat& img = *(Mat*)userdata;
	Mat t;
	cv::cvtColor(img, t, cv::COLOR_RGB2GRAY);
	cv::threshold(t, t, Scroll_value(thre), 255, cv::THRESH_BINARY);
	_imshow(t);
	_imshow(hullsMatrix[Scroll_value(thre)]);
}