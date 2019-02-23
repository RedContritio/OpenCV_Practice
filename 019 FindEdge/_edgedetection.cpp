#include "_edgedetection.h"

namespace RedContritio
{
	namespace Experiment
	{
		cv::Mat getGaussianKernel(cv::Mat ksize, double sigma, int dims)
		{
			cv::Mat res = cv::getGaussianKernel(ksize.at<int>(0, 0), sigma);
			for(int i=1; i<dims; i++)
			{
				res *= cv::getGaussianKernel(ksize.at<int>(0, i), sigma);
			}
			return res;
		}

		void RGB2GRAY(cv::Mat& src, cv::Mat& dst, int flag)
		{
			cv::Mat _dst = cv::Mat(src.size(), CV_8UC1);
			double w[3];
			if(flag & RGB2GRAY_BIO) w[0] = 0.114, w[1] = 0.587, w[2] = 0.299;
			else w[0] = 0.33333, w[1] = 0.33333, w[2] = 0.33333;
			for(int i=0; i<src.rows; ++i)
			{
				for(int j=0; j<src.cols; ++j)
				{
#define TMP_V(k) w[k]*src.at<cv::Vec3b>(i, j)[k]
					double value= TMP_V(0) + TMP_V(1) + TMP_V(2);
#undef TMP_V
					_dst.at<uchar>(i, j) = cv::saturate_cast<uchar>(value);
				}
			}
			dst = _dst;
		}

		void Sobel_on_x(cv::Mat& src, cv::Mat& dst)
		{
			cv::Mat element = (cv::Mat_<double>(3,3) <<		-1,	0,	   1,
														-1.414,	0, 1.414,
															-1, 0,	   1);
			filter2D(src , dst, src.depth(), element);
		}
		
		void Sobel_on_y(cv::Mat& src, cv::Mat& dst)
		{
			cv::Mat element = (cv::Mat_<double>(3,3) << -1, -1.414, -1,
														 0,      0,  0,
														 1,  1.414,  1);
			filter2D(src , dst, src.depth(), element);
		}
	}
}