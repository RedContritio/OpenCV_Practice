#ifndef IMGPROC__INC
#define IMGPROC__INC
#pragma once
#include <core/core.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		void blur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, cv::Point anchor = cv::Point(-1,-1));
		void salt(cv::Mat& src, cv::Mat& dst, double density);
		void MedianFilter_Vec3b(cv::Mat& src, cv::Mat& dst, cv::Size ksize); // Process the anchor is troublesome, so give up it
		bool operator==(const cv::Mat& pic1, const cv::Mat& pic2);
		void MatDifference(cv::Mat& mat1, cv::Mat mat2, bool contrast = true, const char* name = "");
		cv::Mat ChannelDifference(cv::Mat& mat1, cv::Mat& mat2);
		void Normalize(cv::Mat& src, cv::Mat& dst);
	}
}

#endif