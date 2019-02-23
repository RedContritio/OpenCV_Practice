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

int main()
{
	::srand(::time(0));
	Mat img = imread("1.jpg");
	_resize(img, /2);
	_imshow(img);
	Mat blu=img;
	//cv::blur(img, blu, cv::Size(9, 9));
	_imshow(blu);

	Mat gray, bina;
	cv::cvtColor(blu, gray, cv::COLOR_RGB2GRAY);
	_imshow(gray);
	cv::adaptiveThreshold(gray, bina, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);
	//bina = gray > 128;
	_imshow(bina);
	//cv::erode(bina, bina, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
	_imshow((bina));

	Mat cany;
	cv::Canny(bina, cany, 3, 9, 3);
	_imshow(cany);

	Mat mask = Mat::zeros(img.size(), img.type());
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::findContours(bina, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

	for(int index = 0; index >= 0; index = hierarchy[index][0])
	{
		cv::Scalar color(255, 255, 255);
		cv::drawContours(mask, contours, index, color, cv::FILLED, 1, hierarchy);
	}

	Mat dst;
	img.copyTo(dst, mask);
	_imshow(dst);

	waitKey();
	return 0;
}