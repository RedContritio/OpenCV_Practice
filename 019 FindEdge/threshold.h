#ifndef THRESHOLD__INC
#define THRESHOLD__INC
#pragma once

#include <core.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		void threshold(cv::Mat& src, cv::Mat& dst, double thresh, double maxval, int type );
	}
}

#endif