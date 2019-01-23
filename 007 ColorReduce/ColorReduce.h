#ifndef CLR__REDUCE__INC
#define CLR__REDUCE__INC
#pragma once
#include <core/core.hpp>
#include <highgui/highgui.hpp>

#define MethodSelector 3
void ColorReduce( cv::Mat& img, cv::Mat& dst)
{
	int divideWidth = 0x20;
#if MethodSelector == 0 
	uchar table[0x100];
	for( int i=0; i<0x100; i++)
	{
		table[i] = divideWidth*( i/ divideWidth) + divideWidth/ 2;
	}
	cv::Mat LookUpTable( 1, 0x100, CV_8U);
	uchar *p = LookUpTable.data;
	for( int i=0; i<0x100; i++) p[i] = table[i];
	cv::LUT( img, LookUpTable, dst);
#elif MethodSelector == 1
	dst = img.clone();
	int r = img.rows;
	int c = img.cols* img.channels();
	for( int i = 0; i < r; ++i)
	{
		uchar *data = dst.ptr<uchar>( i);
		for( int j = 0; j < c; ++j)
		{
			data[j] = data[j]/ divideWidth* divideWidth+ ( divideWidth/ 2);
		}
	}
#elif MethodSelector == 2
	dst = img.clone();
	cv::Mat_<cv::Vec3b>::iterator it = dst.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator end = dst.end<cv::Vec3b>();

	for( ; it < end; ++it)
	{
		(*it)[0] = (*it)[0]/ divideWidth* divideWidth+ ( divideWidth/ 2);
		(*it)[1] = (*it)[1]/ divideWidth* divideWidth+ ( divideWidth/ 2);
		(*it)[2] = (*it)[2]/ divideWidth* divideWidth+ ( divideWidth/ 2);
	}
#else
	dst = img.clone();
	int r = dst.rows;
	int c = dst.cols;
	for( int i = 0; i < r; ++i)
	{
		for( int j = 0; j < c; ++j)
		{
			for( int k = 0; k < 3; ++k)
			{
				dst.at<cv::Vec3b>( i, j)[k] = dst.at<cv::Vec3b>( i, j)[k]/ divideWidth* divideWidth+ ( divideWidth/ 2);
			}
		}
	}
#endif
}
#endif