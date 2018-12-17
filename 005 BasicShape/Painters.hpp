#ifndef PAINTERS__INC
#define PAINTERS__INC
#pragma once
#include <core.hpp>
#include <imgproc.hpp>

void DrawEllipse( cv::Mat img, double angle, cv::Point p, cv::Size sz)
{
	int thinkness = 2;
	int LineType = 8;
	cv::ellipse( img, p, sz, angle, 0, 360, cv::Scalar( 0xFF, 0x82, 0x00), thinkness, LineType);
}

#endif