#ifndef IMGPROC__INC
#define IMGPROC__INC
#pragma once
#include <core/core.hpp>

#include "pyraid.h"

namespace RedContritio
{
	namespace Experiment
	{
		void blur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, cv::Point anchor = cv::Point(-1,-1));
		void salt(cv::Mat& src, cv::Mat& dst, double density);
		void MedianFilter_Vec3b(cv::Mat& src, cv::Mat& dst, cv::Size ksize); // Process the anchor is troublesome, so give up it
		bool operator==(const cv::Mat& pic1, const cv::Mat& pic2);
		void MatDifference(cv::Mat& mat1, cv::Mat mat2, bool contrast = true, const char* name = "", bool isBlackBack = false);
		cv::Mat ChannelDifference(cv::Mat& mat1, cv::Mat& mat2);
		void Normalize(cv::Mat& src, cv::Mat& dst);
		void inverseColor(cv::Mat& src, cv::Mat& dst);
		void floodFill(cv::Mat img, cv::Point seedPoint, cv::Scalar newVal,
						cv::Rect* rect = 0, cv::Scalar loDiff = cv::Scalar(),cv::Scalar upDiff = cv::Scalar(), int flags = 4 );
	}
}

#endif