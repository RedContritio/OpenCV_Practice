#ifndef TYPE_OPERATION_EXPAND__INC
#define TYPE_OPERATION_EXPAND__INC
#pragma once

#include <core/core.hpp>

namespace RedContritio
{
	namespace Experiment
	{
		namespace OperationExpand
		{

			template<typename T> struct MatElementTypeIndicator
			{
				typedef T type;
			};

			template<typename T> MatElementTypeIndicator<T> getMatElementType(cv::Mat_<T>& m)
			{
				return MatElementTypeIndicator<T>();
			}

			inline cv::Vec3b convert(cv::Scalar v)
			{
				return cv::Vec3b(cv::saturate_cast<uchar>(v[0]),
								 cv::saturate_cast<uchar>(v[1]), 
								 cv::saturate_cast<uchar>(v[2]));
			}

			inline bool operator<(cv::Vec3b a, cv::Vec3b b)
			{
				return (a[0]< b[0]) &&  (a[1]< b[1]) &&  (a[2]< b[2]);
			}
			
			inline bool operator>(cv::Vec3b a, cv::Vec3b b)
			{
				return (a[0]> b[0]) &&  (a[1]> b[1]) &&  (a[2]> b[2]);
			}

			inline bool operator<=(cv::Vec3b a, cv::Vec3b b)
			{
				return (a[0]<= b[0]) &&  (a[1]<= b[1]) &&  (a[2]<= b[2]);
			}
			
			inline bool operator>=(cv::Vec3b a, cv::Vec3b b)
			{
				return (a[0]>= b[0]) &&  (a[1]>= b[1]) &&  (a[2]>= b[2]);
			}

			inline bool operator==(cv::Vec3b a, cv::Vec3b b)
			{
				return (a[0]== b[0]) &&  (a[1]== b[1]) &&  (a[2]== b[2]);
			}

		}
	}
}
#endif