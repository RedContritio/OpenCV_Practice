#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include "MatResize.h"
#include "imgproc_.h"

#include <iostream>

#define NotUseRedContritioMain

char s[256];

#ifndef NotUseRedContritioMain
#include "RedContritioMain.h"

cv::Mat *pmat;

void MatPaintOnHDC(HDC surface, cv::Mat& img)
{
	for(int i=0; i<img.rows; ++i)
	{
		for(int j=0; j<img.cols; ++j)
		{
			auto point = img.at<cv::Vec3b>(i, j);
			SetPixel(surface, j, i, RGB(point[2], point[1], point[0]));
		}
	}
}

void Painter(HDC surface)
{
	//if(pmat) MatPaintOnHDC(surface, *pmat);
}

int RedContritioMain(void)
{
	RegisterRedContritioPainter(Painter);
#else

int main()
{
#endif
	cv::Mat img = cv::imread("1.jpg");

	MatResize(img, *8/15);
	//MatResize(img, *2/3);
	
	cv::imshow("", img);
#ifdef NotUseRedContritioMain

	cv::Mat dst, dst2;
	cv::Mat k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::Point anc(-1, -1);

	//cv::erode(img, dst, k, anc);
	//RedContritio::Experiment::erode(img, dst2, cv::Mat_<uchar>(k), anc);
	//cv::imshow("erode", dst);
	//cv::imshow("erode reco", dst2);
	//printf("erode same? %d\n", RedContritio::Experiment::operator==(dst, dst2));
	//RedContritio::Experiment::MatDifference(dst, dst2, false, "erode");

	//cv::dilate(img, dst, k, anc);
	//RedContritio::Experiment::dilate(img, dst2, cv::Mat_<uchar>(k), anc);
	//cv::imshow("dilate", dst);
	//cv::imshow("dilate reco", dst2);
	//printf("dilate same? %d\n", RedContritio::Experiment::operator==(dst, dst2));
	//RedContritio::Experiment::MatDifference(dst, dst2, true, "dilate");
	
	RedContritio::Experiment::close(img, dst, k, anc);
	cv::imshow("close", dst);

	RedContritio::Experiment::open(img, dst2, k, anc);
	cv::imshow("open", dst2);
	
	//RedContritio::Experiment::MatDifference(dst, dst2, true, "difference");

	//cv::Mat subtract = dst2 - dst;
	//RedContritio::Experiment::inverseColor(subtract, subtract);
	//cv::imshow("subtract", subtract);

	//RedContritio::Experiment::morphologyGradient(img, dst, k, anc);
	//cv::imshow("gradient", dst);
	
	RedContritio::Experiment::tophat(img, dst, k, anc);
	cv::imshow("tophat reco", dst);
	RedContritio::Experiment::inverseColor(dst, dst);
	cv::imshow("tophat inversed reco", dst);

	RedContritio::Experiment::blackhat(img, dst, k, anc);
	cv::imshow("blackhat reco", dst);
	RedContritio::Experiment::inverseColor(dst, dst);
	cv::imshow("blackhat inversed reco", dst);
	//RedContritio::Experiment::close(dst, dst, k, anc);
	//cv::imshow("open-close", dst);

	cv::waitKey();
#endif
	return 0;
}