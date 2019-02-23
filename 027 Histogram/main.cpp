#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "_imgproc.h"

using cv::Mat;

int main(void)
{
	Mat img = cv::imread("1.jpg");
	_resize(img, /2);
	cv::cvtColor(img, img, cv::COLOR_RGB2HSV);
	_imshow(img);

	int HueBinNum = 30;
	int SatBinNum = 32;
	int histSize[] = {HueBinNum, SatBinNum};
	float HueRange[] = {0, 180};
	float SatRange[] = {0, 256};
	auto ranges = {HueRange, SatRange};
	cv::MatND dst;
	cv::waitKey();
	return 0;
}