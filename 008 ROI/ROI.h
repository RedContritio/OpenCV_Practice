#pragma once
#include <opencv2/highgui.hpp>

template<int v> void _ROI(cv::Mat& src, cv::Mat& dst, cv::Rect region)
{
	return _ROI<v-1>(src, dst, region);
}

template<> void _ROI<0>(cv::Mat& src, cv::Mat& dst, cv::Rect region)
{
	dst = src(region);
}

template<> void _ROI<1>(cv::Mat& src, cv::Mat& dst, cv::Rect region)
{
	dst = src(cv::Range(region.y, region.y + region.height), cv::Range(region.x, region.x + region.width));
}

template<> void _ROI<2>(cv::Mat& src, cv::Mat& dst, cv::Rect region)
{
	dst = src.rowRange(region.y, region.y + region.height).colRange(region.x, region.x + region.width);
}