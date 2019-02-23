#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <vector>

#include "_imgproc.h"

using cv::Mat;
using cv::imread;
using cv::imshow;
using cv::waitKey;

using std::vector;

void onMouse(int event, int x, int y, int flags, void* userdata);

Mat img, img_, mask, maskWatershed;

int main()
{
	::srand((unsigned)::time(0));
	img = imread("1.jpg");
	_resize(img, /5);
	img_ = img.clone(), mask = Mat::zeros(img.size(), CV_8UC1);
	mask = Mat::zeros(img.size(), CV_8UC1);
	_imshow(img);
	_imshow(img_);
	cv::setMouseCallback("img_", onMouse, 0);

	waitKey();
	return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	static int areaid = 1;
	static cv::Point point0;
	if(!__LIMIT_POSITION(img_, x, y)) return;
	if(event == cv::EVENT_RBUTTONUP)
	{
		vector<vector<cv::Point>> contours;
		vector<cv::Vec4i> hierarchy;
		cv::findContours(mask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
		//if(contours.size() == 0) return;
		maskWatershed = cv::Mat::zeros(img.size(), CV_32S);
		for(int i=0; i<contours.size(); ++i)
		{
			cv::drawContours(maskWatershed, contours, i, cv::Scalar::all(i+1), 1, 8, hierarchy, INT_MAX);
		}
		cv::watershed(img, maskWatershed);
		vector<cv::Vec3b> colorTab;
		for(int i=0; i<contours.size(); ++i)
		{
			colorTab.push_back(cv::Vec3b(rand()&0xFF, rand()&0xFF, rand()&0xFF));
		}
		Mat dst(img.size(), img.type(), cv::Scalar::all(0));
		for(int i=0; i<img.rows; ++i)
		{
			for(int j=0; j<img.cols; ++j)
			{
				int index = maskWatershed.at<int>(i, j);
				if(index == -1) dst.at<cv::Vec3b>(i, j) = cv::Vec3b::all(255);
				else if(index <=0 || index > contours.size())  dst.at<cv::Vec3b>(i, j) = cv::Vec3b::all(0);
				//else  dst.at<cv::Vec3b>(i, j) = colorTab[index-1];
			}
		}
		Mat shed;
		img.copyTo(shed, dst);
		_imshow(shed);
		double srcRate = 0.4;
		cv::addWeighted(shed, 1-srcRate, img, srcRate, 0, dst);
		_imshow(dst);
	}
	if(event == cv::EVENT_MOUSEWHEEL)
	{
		mask = cv::Scalar::all(0);
		img_ = img.clone();
	}
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		point0 = cv::Point(x, y);
	}
	else if(event == cv::EVENT_MOUSEMOVE&& (flags&cv::EVENT_LBUTTONDOWN))
	{
		cv::Point point1(x, y);
		cv::line(mask, point0, point1, cv::Scalar::all(255), 1);
		cv::line(img_, point0, point1, cv::Scalar::all(255), 1);
		point0 = point1;
	}
	_imshow(img_);
}