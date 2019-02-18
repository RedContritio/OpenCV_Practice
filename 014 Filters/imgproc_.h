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
	}
}

#endif