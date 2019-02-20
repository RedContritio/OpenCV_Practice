#ifndef PYRAID__INC
#define PYRAID__INC
#pragma once

#include <core.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		void pyrDown(cv::Mat& src, cv::Mat& dst);
		void pyrUp(cv::Mat& src, cv::Mat& dst);
	}
}
#endif