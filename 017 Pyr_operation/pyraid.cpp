#include "pyraid.h"

#include <imgproc.hpp>
#include <highgui.hpp>

#define __LIMIT_POSITION(pic,x,y) ( ((x)>=0) && ((x)<((pic).cols)) && ((y)>=0) && ((y)<((pic).rows)) )

namespace RedContritio
{
	namespace Experiment
	{
		void pyrDown(cv::Mat& src, cv::Mat& dst)
		{
			cv::Mat _dst;
			cv::GaussianBlur(src, _dst, cv::Size(3, 3), 0);
			dst = cv::Mat(cv::Size((src.cols+ 1)/ 2, (src.rows+ 1)/ 2), src.type());
			for(int i=0; i<dst.rows; ++i)
			{
				for(int j=0; j<dst.cols; ++j)
				{
					dst.at<cv::Vec3b>(i, j) = _dst.at<cv::Vec3b>(2*i, 2*j);
				}
			}
		}
		
		void pyrUp(cv::Mat& src, cv::Mat& dst)
		{
			cv::Mat _dst = cv::Mat::zeros(cv::Size(src.cols+ src.cols/ 2* 2, src.rows+ src.rows/ 2* 2), src.type());
			cv::Mat _kernel = cv::getGaussianKernel(3, 0);
			cv::Mat kernel_ = cv::getGaussianKernel(3, 0);
			cv::Mat kernel = _kernel * kernel_.t();
			for(int i=0; i<src.rows; ++i)
			{
				for(int j=0; j<src.cols; ++j)
				{
					_dst.at<cv::Vec3b>(2*i, 2*j) = src.at<cv::Vec3b>(i, j);
				}
			}
			for(int i=0; i<_dst.rows; ++i)
			{
				for(int j=0; j<_dst.cols; ++j)
				{
					if(i%2 || j%2)
					{
						double weight = 0;
						double v[3] = {};
						for(int dy = -1; dy <= 1; ++dy)
						{
							for(int dx = -1; dx <= 1; ++dx)
							{
								if( ((dx+ j) % 2 == 0) && ((dy+ i) % 2 == 0) && __LIMIT_POSITION(_dst, j+dx, i+dy))
								{
									double w = kernel.at<double>(dy+1, dx+1);
									weight += w;
									v[0] += w*(1.0*_dst.at<cv::Vec3b>(dy+i, dx+j)[0]);
									v[1] += w*(1.0*_dst.at<cv::Vec3b>(dy+i, dx+j)[1]);
									v[2] += w*(1.0*_dst.at<cv::Vec3b>(dy+i, dx+j)[2]);
									//if(i<10 && j<10)printf("< %d , %d > from < %d , %d > ,weight %g , %g %g %g %g ,from %d %d %d\n",
									//	i, j, i+dy, j+dx, w, weight, v[0], v[1], v[2], _dst.at<cv::Vec3b>(dy+i, dx+j)[0], 
									//	_dst.at<cv::Vec3b>(dy+i, dx+j)[1], _dst.at<cv::Vec3b>(dy+i, dx+j)[2]);
								}
							}
						}
						v[0]/=weight, v[1]/=weight, v[2]/=weight;
						_dst.at<cv::Vec3b>(i, j) = cv::Vec3b(cv::saturate_cast<uchar>(v[0]), cv::saturate_cast<uchar>(v[1]), cv::saturate_cast<uchar>(v[2]));
					}
				}
			}
			dst = _dst;
		}
	}
}