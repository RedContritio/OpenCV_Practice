#ifndef IMGPROC__INC
#define IMGPROC__INC
#pragma once
#include <core/core.hpp>

namespace RedContritio
{
	namespace Experiment
	{

		#define SCALE_RATE(x,operation) x operation

		#define MatResize(img,operation) cv::resize(img, img, SCALE_RATE(img.size(), operation))

		void blur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, cv::Point anchor = cv::Point(-1,-1));
		void GaussianBlur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, double sigmaX = 0);
		void salt(cv::Mat& src, cv::Mat& dst, double density);
		void MedianFilter_Vec3b(cv::Mat& src, cv::Mat& dst, cv::Size ksize); // Process the anchor is troublesome, so give up it
		bool operator==(const cv::Mat& pic1, const cv::Mat& pic2);
		void MatDifference(cv::Mat& mat1, cv::Mat mat2, bool contrast = true, const char* name = "", bool isBlackBack = false);
		cv::Mat ChannelDifference(cv::Mat& mat1, cv::Mat& mat2);
		void Normalize(cv::Mat& src, cv::Mat& dst);

		template<typename T, int n> void inverseColor(cv::Mat& src, cv::Mat& dst)
		{
			dst = src.clone();
			std::for_each(dst.begin<cv::Vec<T,n>>(), dst.end<cv::Vec<T,n>>(), [](cv::Vec<T,n>& v){for(int i=0; i<n; i++)v[i] = ~v[i];});
		}

		void floodFill(cv::Mat img, cv::Point seedPoint, cv::Scalar newVal,
						cv::Rect* rect = 0, cv::Scalar loDiff = cv::Scalar(),cv::Scalar upDiff = cv::Scalar(), int flags = 4 );
	}
}

#endif