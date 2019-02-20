#ifndef MORPHOLOGY__INC
#define MORPHOLOGY__INC
#pragma once
#include <core/core.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		void erode(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor = cv::Point(-1,-1));
		void dilate(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor = cv::Point(-1,-1));

		void open(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor = cv::Point(-1,-1));
		void close(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor = cv::Point(-1,-1));

		void morphologyGradient(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, 
								cv::Point anchor = cv::Point(-1,-1), bool isBlackBack = false);

		void tophat(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, 
								cv::Point anchor = cv::Point(-1,-1));
		void blackhat(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, 
								cv::Point anchor = cv::Point(-1,-1));
	}
}
#endif