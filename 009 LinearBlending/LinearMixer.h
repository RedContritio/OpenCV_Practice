#ifndef LINEARMIXER__INC
#define LINEARMIXER__INC
#pragma once
#include <highgui/highgui.hpp>

#define OVERLOADED_MACRO(M, ...) __OVERLOAD_MACRO(M, __COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)
#define __OVERLOAD_MACRO(macroname, number_of_args) __MACRO_EXPEND(macroname, number_of_args)
#define __MACRO_EXPEND(macroname, overloadid) macroname##overloadid

#define __COUNT_ARGS(...) __ARG_PATTERN_MATCH(__VA__ARGS, 10, 9, 8 ,7, 6, 5, 4, 3, 2, 1)// doesn't work, because \
																						only be expanded into single macro
#define __ARG_PATTERN_MATCH(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N 

#define LINEARMIX_FULL( src1, alpha, src2, beta, gamma, dst, dtype) cv::addWeighted(src1, alpha, src2, beta, gamma, dst, dtype)
#define LinearMix1( pic1, alpha, pic2, dst) cv::addWeighted(pic1, alpha, pic2, 1.0-(alpha), 0.0, dst)

//#define LinearMix(...) OVERLOADED_MACRO(LinearMix, __VA_ARGS__) 
// The processor doesn't expand macro correctly, so I have to use function overload.

#define __TRY_CATCH_THROW__(statement) do{ \
											try{ \
												statement; \
											} \
											catch(cv::Exception e){ \
												throw(e); \
											}}while(0);


void LinearMix(cv::Mat& img1, cv::Mat& img2, cv::Mat& dst, double alpha, double beta, double gamma, int dtype)
{
	__TRY_CATCH_THROW__(cv::addWeighted(img1, alpha, img2, beta, gamma, dst, dtype));
}
void LinearMix(cv::Mat& img1, cv::Mat& img2, cv::Mat& dst, double alpha, double beta, double gamma)
{
	__TRY_CATCH_THROW__(LinearMix(img1, img2, dst, alpha, beta, gamma, -1));
}
void LinearMix(cv::Mat& img1, cv::Mat& img2, cv::Mat& dst, double alpha, double beta)
{
	__TRY_CATCH_THROW__(LinearMix(img1, img2, dst, alpha, beta, 0));
}
void LinearMix(cv::Mat& img1, cv::Mat& img2, cv::Mat& dst, double alpha)
{
	__TRY_CATCH_THROW__(LinearMix(img1, img2, dst, alpha, 1-alpha));
}
#endif