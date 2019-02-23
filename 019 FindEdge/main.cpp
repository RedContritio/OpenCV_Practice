#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include "_imgproc.h"

#include <iostream>
#include <vector>

void CannyTest(cv::Mat img);
void SobelTest(cv::Mat img);

void SobelRecoTest(cv::Mat img);

int main(void)
{
	cv::Mat img = cv::imread("1.jpg", 1);
	MatResize(img, *1/3);
	cv::imshow("s", img);
	cv::Mat dst, dstr;

	//RedContritio::Experiment::RGB2GRAY(img, dstr, 1);
	//cv::imshow("gray reco", dstr);
	
	//CannyTest(img);
	//SobelTest(img);
	SobelRecoTest(img);
	
	//RedContritio::Experiment::GaussianBlur(img, dstr, cv::Size(5, 5), 0);
	//cv::imshow("dst reco", dstr);
	//cv::GaussianBlur(img, dst, cv::Size(3, 3), 0);
	//cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
	//cv::imshow("g", img);
	//cv::morphologyEx(img, img, cv::MORPH_ERODE,cv::getStructuringElement(cv::MORPH_RECT, cv::Size(11, 11)));
	//cv::imshow("er", img);
	//cv::morphologyEx(img, img, cv::MORPH_BLACKHAT,cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11)));
	//cv::imshow("bh", img);


	//RedContritio::Experiment::inverseColor<uchar,1>(dst, dst);
	//cv::imshow("rev", dst);
	cv::waitKey();
	return 0;
}

void CannyTest(cv::Mat img){
	cv::Mat dst;
	std::vector<cv::Mat> cha;
	cv::split(img, cha);

	for(int i=0; i<cha.size(); ++i)
	{
		cv::GaussianBlur(cha[i], cha[i], cv::Size(3, 3), 0);
		cv::Canny(cha[i], cha[i], 3, 9, 3);
		for(auto it = cha[i].begin<uchar>(); it != cha[i].end<uchar>(); ++it) *it = ~*it;
	}
	cv::merge(cha, dst);
	cv::imshow("edge", dst);
	
	cv::Canny(img, dst, 3, 9, 3);
	img.copyTo(dst, dst);
	for(auto it = dst.begin<cv::Vec3b>(); it != dst.end<cv::Vec3b>(); ++it) for(auto i=0; i<3; ++i) (*it)[i] = ~(*it)[i];
	cv::imshow("mask", dst);
}

void SobelTest(cv::Mat img)
{
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y, dst;
#define Sobel_on_(w,x,y) cv::Sobel(img, grad_##w, CV_16S, x, y, 3, 1, 1); cv::convertScaleAbs(grad_##w, abs_grad_##w); cv::imshow(#w " sobel", abs_grad_##w);
	Sobel_on_(x, 1, 0);
	Sobel_on_(y, 0, 1);
	cv::addWeighted(abs_grad_x, 1, abs_grad_y, 1, 0, dst);
	for(auto it = dst.begin<cv::Vec3b>(); it != dst.end<cv::Vec3b>(); ++it) for(auto i=0; i<3; ++i) (*it)[i] = ~(*it)[i];
	cv::imshow("sobel result", dst);
	cv::imwrite("3.jpg", dst);
}


void SobelRecoTest(cv::Mat img)
{
	cv::Mat dst, dstr;
	RedContritio::Experiment::Sobel_on_x(img, dst);
	cv::imshow("sx", dst);

	RedContritio::Experiment::Sobel_on_y(img, dstr);
	cv::imshow("sy", dstr);

	cv::addWeighted(dst, 1, dstr, 1, 0, dstr);
	//for(auto it = dstr.begin<cv::Vec3b>(); it != dstr.end<cv::Vec3b>(); ++it) for(auto i=0; i<3; ++i) (*it)[i] = ~(*it)[i];
	cv::imshow("s reco", dstr);

	RedContritio::Experiment::threshold(dstr, dstr, 127, 255, cv::THRESH_TOZERO);
	cv::imshow("s threshold reco", dstr);

	cv::morphologyEx(dstr, dstr, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
	cv::imshow("s close reco", dstr);

	img.copyTo(dst, dstr);
	cv::imshow("s mask reco", dst);
}