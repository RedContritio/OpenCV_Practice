#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include "MatResize.h"
#include "imgproc_.h"
#include "CompileMessage.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

const int sc_width = 1536;
const int sc_height = 864;

void BlurTest(cv::Mat& img);
void MedianFilterTest(cv::Mat& img);
void BilateralFilterTest(cv::Mat& img);
void FiltersTest(cv::Mat& img);

void TrackBarTest(cv::Mat& img);
void onScroll(int , void*);
#define KSIZE_NAME(name) g_##name##KernelSize
int KSIZE_NAME(box), KSIZE_NAME(blur), KSIZE_NAME(Gaussian);
#define CTTBC_NAME(name) g_##name##Count
#define CTTBC_DECLARE(name) CTTBC_NAME(name) = 100
const int CTTBC_DECLARE(box), CTTBC_DECLARE(blur), CTTBC_DECLARE(Gaussian);

cv::Mat img ;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	img = cv::imread("1.jpg");

	MatResize(img, *20/60);

	cv::Mat img_ = img;
	//MatResize(img_, *1/3);
	cv::imshow("",img_);
	cv::moveWindow("", 0, 0);

	//BlurTest(img);
	
	printf("is same ? %d\n", RedContritio::Experiment::operator==(img, img));
	cv::Mat dst;
	RedContritio::Experiment::salt(img_, dst, 0.01);
	cv::imshow( "salt", dst);
	cv::moveWindow("salt", 0, img_.rows);
	printf("is same ? %d\n", RedContritio::Experiment::operator==(dst, img));
	//MatDifference(dst, img);
	
	MedianFilterTest(dst);
	//BilateralFilterTest(dst);
	//FiltersTest(img);

	//TrackBarTest(img);

	while(static_cast<char>(cv::waitKey(1))!=' ');
	return 0;
}



void BlurTest(cv::Mat& img)
{
	cv::Mat dst, dst2;
	cv::blur(img, dst, cv::Size(10, 10));
	cv::imshow("dst", dst);
	//return ;

	// I do not want to run it 
	RedContritio::Experiment::blur(img, dst2, cv::Size(1, 1)); // As we all know, function in RedContritio is slow and filled with bugs
	cv::imshow("dst2", dst2);
	return ;
}

void MedianFilterTest(cv::Mat& img)
{
#pragma message(__MESSAGE_INFO("There are some differences in Median Filter's effect, but I don't know why."))
	int ksz = 5;
	auto sz = cv::Size(ksz, ksz);
	cv::Mat dst, dst2;
	cv::medianBlur(img, dst, ksz);
	cv::imshow("dst", dst);
	//return ;

	RedContritio::Experiment::MedianFilter_Vec3b(img, dst2, sz); // again, function in RedContritio is slow and filled with bugs
	
	RedContritio::Experiment::MatDifference(dst, dst2, false);
	cv::imshow("dst2", dst2);
	return ;
}

void BilateralFilterTest(cv::Mat& img)
{
	int d = 3;
	cv::Mat dst;
	cv::bilateralFilter(img, dst, d, d*2, d/2);
	cv::imshow("dst", dst);
	printf("is same ? %d\n", RedContritio::Experiment::operator==(dst, img));
	RedContritio::Experiment::MatDifference(dst, img);
	//return ;

	//cv::imshow("dst2", dst2);
	return ;
}
#define DST(name) DST_##name
#define DTITLE(name) "DST_" #name
#define DIMSHOW(name) cv::imshow(DTITLE(name), DST(name))
void FiltersTest(cv::Mat& img)
{
	cv::Size sz(9, 9);
	cv::Mat DST(box), DST(blur), DST(Gaussian);
	cv::boxFilter(img, DST(box), -1, sz);
	DIMSHOW(box);

	cv::blur(img, DST(blur), sz);
	DIMSHOW(blur);

	DST(Gaussian) = img.clone();
	try
	{
		cv::GaussianBlur(img, DST(Gaussian), sz, 0);
	}
	catch(cv::Exception e)
	{
		std::cout<< e.msg; // Gaussian blur must have an odd height and odd width.
	}
	DIMSHOW(Gaussian);
	return ;
}

void TrackBarTest(cv::Mat& img)
{
	cv::namedWindow("Track Bar");
	cv::moveWindow("Track Bar", img.cols*1/3, 0);
	cv::createTrackbar("boxFilter :", "Track Bar", &KSIZE_NAME(box), CTTBC_NAME(box), onScroll);
	cv::createTrackbar("Blur :", "Track Bar", &KSIZE_NAME(blur), CTTBC_NAME(blur), onScroll);
	cv::createTrackbar("Gaussian :", "Track Bar", &KSIZE_NAME(Gaussian), CTTBC_NAME(Gaussian), onScroll);
}

#define KSIZE_MAKE_(name,op) cv::Size(KSIZE_NAME(name) op, KSIZE_NAME(name)+1)
#define KSIZE_MAKE(name) KSIZE_MAKE_(name,+1)

void onScroll(int , void*)
{
	cv::Mat dst = img.clone();
	MatResize(dst, *2/5);
	cv::Mat part[3] = {dst.clone(), dst.clone(), dst.clone()};
	dst = img.clone();
	MatResize(dst, *2/3);

	cv::boxFilter(dst, dst, -1, KSIZE_MAKE(box));
	cv::boxFilter(part[0], part[0], -1, KSIZE_MAKE(box));
	cv::imshow("box only", part[0]);
	cv::moveWindow("box only", sc_width-part[0].cols, 0);

	cv::blur(dst, dst, KSIZE_MAKE(blur));
	cv::blur(part[1], part[1], KSIZE_MAKE(blur));
	cv::imshow("blur only", part[1]);
	cv::moveWindow("blur only", sc_width-part[1].cols, part[0].rows);

	try
	{
		cv::GaussianBlur(dst, dst, KSIZE_MAKE_(Gaussian,/2*2+1), 0, 0);
		cv::GaussianBlur(part[2], part[2], KSIZE_MAKE_(Gaussian,/2*2+1), 0, 0);
		cv::imshow("Gaussian only", part[2]);
		cv::moveWindow("Gaussian only", sc_width-part[2].cols, part[0].rows+ part[1].rows);
	}
	catch(cv::Exception e)
	{
		std::cout<< e.msg<< std::endl;
	}
	imshow("Track Bar", dst);
}