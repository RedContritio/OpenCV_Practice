#include "threshold.h"
#include "TypeOperationEx_.hpp"

#include <imgproc.hpp>

#include <functional>

namespace RedContritio
{
	namespace Experiment
	{
		typedef void (*Vec3bOperation)(cv::Vec3b&);
		template<typename T> void value_negative(T& v){ v = ~v;}

		#define mat_for_each(img,type,it) for(auto it=(img).begin<type>(); it != (img).end<type>(); ++it)
		#define arr_for_each(s,t,loop_i) for(int loop_i=(s); loop_i!=(t); ++loop_i)
		#define mat_for_each_component(img,type,s,t,f) mat_for_each(img,type,it) arr_for_each(s,t,lpi) (f)((*it)[lpi]);
		template<typename T, int n>void for_each_component(cv::Vec<T, n>& v, void (*fun)(T&))
		{
			for(int i=0; i<n; ++i) fun(v[i]);
		}

		void threshold(cv::Mat& src, cv::Mat& dst, double thresh, double maxval, int type )
		{
			dst = src.clone();
			uchar maxv = cv::saturate_cast<uchar>(maxval);
			uchar thre = cv::saturate_cast<uchar>(thresh);
			switch(type)
			{
				case cv::THRESH_BINARY:
				{
					mat_for_each_component(dst,cv::Vec3b, 0, 3, [&](uchar& v){ v=v>thre?maxv:0;});
					break;
				}
				case cv::THRESH_BINARY_INV:
				{
					mat_for_each_component(dst,cv::Vec3b, 0, 3, [&](uchar& v){ v=v>thre?0:maxv;});
					break;
				}
				case cv::THRESH_TRUNC:
				{
					mat_for_each_component(dst,cv::Vec3b, 0, 3, [&](uchar& v){ v=v>thre?thre:v;});
					break;
				}
				case cv::THRESH_TOZERO:
				{
					mat_for_each_component(dst,cv::Vec3b, 0, 3, [&](uchar& v){ v=v>thre?v:0;});
					break;
				}
				case cv::THRESH_TOZERO_INV:
				{
					mat_for_each_component(dst,cv::Vec3b, 0, 3, [&](uchar& v){ v=v>thre?0:v;});
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
}