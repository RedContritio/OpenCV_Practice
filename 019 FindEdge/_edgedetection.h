#ifndef __EDGE_DETECTION__INC
#define __EDGE_DETECTION__INC
#pragma once
#include <core.hpp>
#include <imgproc.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		cv::Mat getGaussianKernel( cv::Size ksize, double sigma, int dims);

		enum RGB2GRAY_FLAGS
		{
			RGB2GRAY_NORMAL = 0, RGB2GRAY_BIO = 1
		};

		void RGB2GRAY(cv::Mat& src, cv::Mat& dst, int flag);

		void Sobel_on_x(cv::Mat& src, cv::Mat& dst); // 3*3 sobel
		void Sobel_on_y(cv::Mat& src, cv::Mat& dst); // 3*3 sobel
	}
}
#endif