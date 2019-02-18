#include "imgproc_.h"
#include <cstdlib>
#include <ctime>

namespace RedContritio
{
	namespace Experiment
	{
		void blur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, cv::Point anchor)
		{
			dst = cv::Mat(src.size(), src.type());
			for(int i=0 - ksize.height; i<src.rows; i++)
			{
				for(int j=0 - ksize.width; j<src.cols; j++)
				{
					int v[3] = {};
					int count = 0;
					for(int m=0; m < ksize.height; ++m)
					{
						for(int n=0; n < ksize.width; ++n)
						{
							if(i+m >=0 &&i+m < src.rows && j+n >=0 && j+n < src.cols)
							{
								cv::Vec3b& rgb = src.at<cv::Vec3b>(i+m,j+n);
								count ++;
								v[0] += rgb[0];
								v[1] += rgb[1];
								v[2] += rgb[2];
							}
						}
					}
				
					int px, py;
					if( anchor.x < 0 || anchor.y < 0)
					{
						px = j+ ksize.width/2;
						py = i+ ksize.height/2;
					}
					else
					{
						px = j+anchor.x;
						py = i+anchor.y;
					}
					if( px >= 0 && px < src.cols && py >= 0 && py < src.rows)
					{
						dst.at<cv::Vec3b>(py, px)[0] = cv::saturate_cast<uchar>(v[0] / count);
						dst.at<cv::Vec3b>(py, px)[1] = cv::saturate_cast<uchar>(v[1] / count);
						dst.at<cv::Vec3b>(py, px)[2] = cv::saturate_cast<uchar>(v[2] / count);
					}
				}
			}
		}

		void salt(cv::Mat& src, cv::Mat& dst, double density)
		{
			dst = cv::Mat(src.size(), src.type());
			for(int i=0; i < src.rows; ++i)
			{
				uchar *psrc = src.ptr<uchar>(i);
				uchar *data = dst.ptr<uchar>(i);
				for(int j=0; j < src.cols; ++j)
				{
					if(density >(rand()/(RAND_MAX+1.0)))
					{
						uchar _salt = (rand()%2)*255;
						for(int k=0; k < src.channels(); ++k)
						{
							data[j*src.channels()+k] = _salt;
						}
					}
					else
					{
						for(int k=0; k < src.channels(); ++k)
						{
							data[j*src.channels()+k] = psrc[j*src.channels()+k];
						}
					}
				}
			}
		}
	}
}