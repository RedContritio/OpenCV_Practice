#include "Morphology_.h"
#include <imgproc/imgproc.hpp>

#define __LIMIT_POSITION(pic,x,y) ( ((x)>=0) && ((x)<((pic).cols)) && ((y)>=0) && ((y)<((pic).rows)) )
namespace RedContritio
{
	namespace Experiment
	{
		namespace
		{
			inline bool lessthan(const cv::Vec3b& a, const cv::Vec3b& b)
			{
				int a0 = a[0], a1 = a[1], a2 = a[2];
				int b0 = b[0], b1 = b[1], b2 = b[2];
				//return (a0*a0+ a1*a1+ a2*a2) < (b0*b0+ b1*b1+ b2*b2);
				return (a0+ a1+ a2) < (b0+ b1+ b2);
				//return (a[0] < b[0]) || (a[1] < b[1]) || (a[2] < b[2]);
			}
			inline bool greaterthan(const cv::Vec3b& a, const cv::Vec3b& b)
			{
				int a0 = a[0], a1 = a[1], a2 = a[2];
				int b0 = b[0], b1 = b[1], b2 = b[2];
				//return (a0*a0+ a1*a1+ a2*a2) > (b0*b0+ b1*b1+ b2*b2);
				return (a0+ a1+ a2) > (b0+ b1+ b2);
				//return (a[0] > b[0]) || (a[1] > b[1]) || (a[2] > b[2]);
			}


			void MatExtreme(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, 
							cv::Point anchor, bool (*cmp)(const cv::Vec3b&, const cv::Vec3b&))
			{
			int px, py;
			CV_Assert(src.data && src.cols > 0 && src.rows > 0);
			CV_Assert(kernel.data && kernel.cols > 0 && kernel.rows > 0);
			CV_Assert(cmp);
			
			cv::Mat dst_ = cv::Mat(src.size(), src.type());
			if(anchor.x < 0 || anchor.y < 0) anchor.x = kernel.cols/2, anchor.y = kernel.rows/2;
			for(int i=0; i<src.rows; ++i)
			{
				for(int j=0; j<src.cols; ++j)
				{
					px = j-anchor.x, py = i-anchor.y;
					if( px >= src.cols || px+kernel.cols < 0 || py >= src.rows || py+kernel.rows < 0)continue;
					cv::Vec3b v;
					bool a = false;
					for(int m=0; m<kernel.rows; ++m)
					{
						for(int n=0; n<kernel.cols; ++n)
						{
							if(__LIMIT_POSITION(src, px+n, py+m))
							{
								if(kernel.at<uchar>(m, n))
								{
									if(!a)
									{
										v = src.at<cv::Vec3b>(py+m, px+n);
										a = true;
									}
									if(cmp(src.at<cv::Vec3b>(py+m, px+n) ,v))
									{
										v = src.at<cv::Vec3b>(py+m, px+n);
									}
								}
							}
						}
					}

					dst_.at<cv::Vec3b>(i, j) = v;
				}
			}

			dst = dst_;
			}


		}

		void erode(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor )
		{
			MatExtreme(src, dst, kernel, anchor, lessthan);
		}

		void dilate(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor )
		{
			MatExtreme(src, dst, kernel, anchor, greaterthan);
		}
		
		void open(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor)
		{
			erode(src, dst, kernel, anchor);
			dilate(dst, dst, kernel, anchor);
			//dilate(src, dst, kernel, anchor); // copy & paste make more than 90% error
		}
		
		void close(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor)
		{
			dilate(src, dst, kernel, anchor);
			erode(dst, dst, kernel, anchor);
		}
		
		void morphologyGradient(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor, bool isBlackBack)
		{
			cv::Mat op, cl;
			open(src, op, kernel, anchor);
			close(src, cl, kernel, anchor);
			dst = op - cl;
			if(!isBlackBack)std::for_each(dst.begin<cv::Vec3b>(), dst.end<cv::Vec3b>(), [](cv::Vec3b& v){v[0] = ~v[0], v[1] = ~v[1], v[2] = ~v[2];});
		}

		void tophat(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor)
		{
			cv::Mat op;
			open(src, op, kernel, anchor);
			dst = src - op;
		}
		void blackhat(cv::Mat& src, cv::Mat& dst, cv::Mat_<uchar> kernel, cv::Point anchor)
		{
			cv::Mat cl;
			close(src, cl, kernel, anchor);
			dst = cl- src;
		}
	}
}