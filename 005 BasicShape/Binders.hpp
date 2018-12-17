#ifndef BINDERS__INC
#define BINDERS__INC
#pragma once

#include <core.hpp>
#include <core/core_c.h>
#include <core/utility.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>

// assert: func is void (*)( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thinkness, int lineType ,int shift )
template< typename func> struct _PainterFunction
{
	_PainterFunction(func f):m_fun( f){}
	void operator()( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thinkness, int lineType ,int shift )
	{
		m_fun( img, p, sz, color, angle, thinkness, lineType, shift);
	}
	void operator()( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thinkness, int lineType)
	{
		this->operator()( img, p, sz, color, angle, thinkness, cv::LINE_8, 0);
	}
	void operator()( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thinkness)
	{
		this->operator()( img, p, sz, color, angle, thinkness, cv::LINE_8);
	}
	void operator()( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle)
	{
		this->operator()( img, p, sz, color, angle, 1);
	}
	void operator()( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color)
	{
		this->operator()( img, p, sz, color, 0);
	}

	func m_fun ;
};
typedef _PainterFunction<void(*)( cv::Mat, cv::Point, cv::Size, cv::Scalar, double, int, int, int)> PainterFunctionType;

void (*(painter_[]))( cv::Mat, cv::Point, cv::Size, cv::Scalar, double, int, int, int) =
{
	[]( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thickness , int lineType , int shift)
	{
		cv::ellipse( img, p, sz, angle, 0, 360, color, thickness, lineType, shift); //x+-> y+-> x--> y-
	},
	[]( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thickness , int lineType , int shift)
	{
		cv::circle( img, p, sz.width, color, thickness, lineType, shift);
	},
	[]( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thickness , int lineType , int shift)
	{
		cv::line( img, p, cv::Point( p.x+sz.width, p.y+sz.height), color, thickness, lineType, shift);
	},
	[]( cv::Mat img, cv::Point p, cv::Size sz, cv::Scalar color, double angle, int thickness , int lineType , int shift)
	{
		cv::rectangle( img, p, cv::Point( p.x+sz.width, p.y+sz.height), color, thickness, lineType, shift);
	},
};

PainterFunctionType painter[]
{
	PainterFunctionType(painter_[0] ),
	PainterFunctionType(painter_[1] ),
	PainterFunctionType(painter_[2] ),
	PainterFunctionType(painter_[3] ),
};



#endif