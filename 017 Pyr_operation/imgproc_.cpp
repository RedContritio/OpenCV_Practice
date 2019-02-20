#include "TypeOperationEx_.hpp"
#include "imgproc_.h"
#include "highgui/highgui.hpp"

#include <imgproc/imgproc.hpp>

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

namespace RedContritio
{
	namespace Experiment
	{
		#define __LIMIT_POSITION(pic,x,y) ( ((x)>=0) && ((x)<((pic).cols)) && ((y)>=0) && ((y)<((pic).rows)) )
		void blur(cv::Mat& src, cv::Mat& dst, cv::Size ksize, cv::Point anchor)
		{
			dst = cv::Mat(src.size(), src.type());
			auto t = -(double)cv::getTickCount();
			#define __ACCESS_ACCERALATION 2
			#if __ACCESS_ACCERALATION == 0
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
			#elif __ACCESS_ACCERALATION == 1
			std::vector<uchar*> sptr, dptr; // with std::vector be used, it will be terribly slow.
			for(int i=0; i<src.rows; i++)
			{
				sptr.push_back(src.ptr<uchar>(i));
				dptr.push_back(dst.ptr<uchar>(i));
			}
			int numChannels = src.channels();
			for(int i=0 ; i<src.rows; i++)
			{
				for(int j=0 ; j<src.cols; j++)
				{
					int v[4] = {};
					int count = 0;
					int px, py;
					if( anchor.x < 0 || anchor.y < 0)
					{
						px = j- ksize.width/2;
						py = i- ksize.height/2;
					}
					else
					{
						px = j-anchor.x;
						py = i-anchor.y;
					}

					for(int m=0; m < ksize.height; ++m)
					{
						for(int n=0; n < ksize.width; ++n)
						{
							if(py+m >=0 &&py+m < src.rows && px+n >=0 && px+n < src.cols)
							{
								count ++;
								for(int k=0; k < numChannels; ++k)
								{
									v[k] += sptr[py+m][numChannels*(px+n)+k];
								}
							}
						}
					}
					
					for(int k=0; k < numChannels; ++k)
					{
						dptr[i][j*numChannels+k] = cv::saturate_cast<uchar>(v[k] / count);
					}
				}
			}
			#elif __ACCESS_ACCERALATION == 2
			uchar *sptr, *dptr;
			sptr = src.data;
			dptr = dst.data;
			int numChannels = src.channels();
			int nlinc = numChannels * src.cols;

			for(int j=0; j < src.cols; ++j)
			{
				for(int i=0; i < src.rows; ++i)
				{
					auto drp = dptr+ i*nlinc+ j*numChannels;
					int v[4] = {};
					int count = 0;
					int dx, dy;
					if( anchor.x < 0 || anchor.y < 0)
					{
						dx = -ksize.width/2;
						dy = -ksize.height/2;
					}
					else
					{
						dx = -anchor.x;
						dy = -anchor.y;
					}
					
					for(int m=0; m < ksize.height; ++m)
					{
						for(int n=0; n < ksize.width; ++n)
						{
							if(i+dy+m >=0 &&i+dy+m < src.rows && j+dx+n >=0 && j+dx+n < src.cols)
							{
								count ++;
								for(int k=0; k < numChannels; ++k)
								{
									v[k] += sptr[(i+dy+m)*nlinc+(j+dx+n)*numChannels+k];
								}
							}
						}
					}

					for(int k=0; k < numChannels; ++k)
					{
						*(drp++) = cv::saturate_cast<uchar>(v[k] / count);
					}
				}
			}
			#endif
			
			t += (double)cv::getTickCount();
			std::cout<< "time: "<< (t*1000/cv::getTickFrequency())<< " ms"<< std::endl;
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

		
		void MedianFilter_Vec3b(cv::Mat& src, cv::Mat& dst, cv::Size ksize)
		{
			::fprintf(stderr, "Notice: matrix must be Vec3b or Vec4b\n");
			cv::Mat dst_ = cv::Mat(src.size(), src.type());
			int *arr = (int *)::malloc(ksize.width* ksize.height* sizeof(int));
			int *alp = (int *)::malloc((ksize.width* ksize.height+ 1)* sizeof(int));
			int *arp = (int *)::malloc((ksize.width* ksize.height+ 1)* sizeof(int));
			for(int i=0; i<=ksize.width* ksize.height; ++i)
			{
				alp[i] = (i+ 1)/ 2 -1;
				arp[i] = (i/ 2)+ 1 -1;
			}

			for(int i=0; i<src.rows; ++i)
			{
				for(int j=0; j<src.cols; ++j)
				{
					int px, py, count = 0;
					py = i-ksize.height/2;
					for(int m=0; m<ksize.height; ++m, ++py)
					{
						px = j-ksize.width/2;
						for(int n=0; n<ksize.width; ++n, ++px)
						{
							if(__LIMIT_POSITION(src,px,py))
							{
								auto p = src.at<cv::Vec3b>(py,px);
								arr[count] = 0;
								uchar *ptk = (uchar *)&arr[count];
								for(int k=0; k < 3; ++k) ptk[k] = p[k];
								++count;
							}
						}
					}
					
					std::sort(arr,arr+count);
					uchar* plt = (uchar *)&arr[alp[count]];
					uchar* prt = (uchar *)&arr[arp[count]];
					for(int k=0; k < 3; ++k) dst_.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>((((int)plt[k])+prt[k])/2);
				}
			}

			::free(arr);
			::free(alp);
			::free(arp);

			dst = dst_;
		}


		bool operator==(const cv::Mat & pic1, const cv::Mat & pic2)
		{
			printf("== testing...\n");
			if(pic1.data == pic2.data) return true;
			printf("data different, testing...\n");
			if( !pic1.data || !pic2.data) return false; 
			printf("not NULL mat, testing...\n");
			if(pic1.rows != pic2.rows || pic1.cols != pic2.cols) return false;
			printf("same size, testing...\n");
			for(int i=0; i < pic1.rows; ++i)
			{
				for(int j=0; j < pic2.cols; ++j)
				{
					if( pic1.at<cv::Vec3b>(i, j) != pic2.at<cv::Vec3b>(i, j))
					{
						std::cout<< "different pixel at "<< i<< " "<< j
							<< " ,former is "<< pic1.at<cv::Vec3b>(i, j)
							<< " latter is "<< pic2.at<cv::Vec3b>(i, j)<< std::endl;
						return false;;
					}
				}
			}
			printf("no different pixel, test end\n");
			return true;
		}
		
		/** @when backcolor is white, blue means the former color is less than the latter
			@when backcolor is black, yellow means the former color is less than the latter
		*/
		cv::Mat ChannelDifference(cv::Mat& mat1, cv::Mat& mat2)
		{
			CV_Assert(mat1.data && mat2.data);
			CV_Assert(mat1.size() == mat2.size());
			CV_Assert(mat1.channels() == mat2.channels() && mat1.channels() == 1);
			cv::Mat dif = cv::Mat::zeros(mat1.size(), CV_8UC3);
			for(int i=0; i < mat1.rows; ++i)
			{
				for(int j=0; j < mat1.cols; ++j)
				{
					if(mat1.at<uchar>(i, j) > mat2.at<uchar>(i, j))
					{
						dif.at<cv::Vec3b>(i, j)[0] = mat1.at<uchar>(i, j) - mat2.at<uchar>(i, j);
						dif.at<cv::Vec3b>(i, j)[1] = mat1.at<uchar>(i, j) - mat2.at<uchar>(i, j);
					}
					else if(mat1.at<uchar>(i, j) < mat2.at<uchar>(i, j))
					{
						dif.at<cv::Vec3b>(i, j)[1] = mat2.at<uchar>(i, j) - mat1.at<uchar>(i, j);
						dif.at<cv::Vec3b>(i, j)[2] = mat2.at<uchar>(i, j) - mat1.at<uchar>(i, j);
					}
				}
			}
			return dif;
		}
		
		void Normalize(cv::Mat& src, cv::Mat& dst)
		{
			uchar maxv = 0 ;
			int ncc = src.cols * src.channels();
			cv::Mat dst_ = cv::Mat::zeros(src.size(), src.type());
			for(int i=0; i<src.rows; ++i)
			{
				auto p = src.ptr<uchar>(i);
				for(int j=0; j<ncc; ++j)
				{
					if(p[j] > maxv) maxv = p[j];
				}
			}

			if(maxv == 0) return ;

			for(int i=0; i<dst_.rows; ++i)
			{
				auto ps = src.ptr<uchar>(i);
				auto pd = dst_.ptr<uchar>(i);
				for(int j=0; j<ncc; ++j)
				{
					pd[j] = cv::saturate_cast<uchar>( 255.0* ps[j]/ maxv);
				}
			}
			dst = dst_;
		}
		
		void inverseColor(cv::Mat& src, cv::Mat& dst)
		{
			dst = src.clone();
			std::for_each(dst.begin<cv::Vec3b>(), dst.end<cv::Vec3b>(), [](cv::Vec3b& v){v[0] = ~v[0], v[1] = ~v[1], v[2] = ~v[2];});
		}

		void MatDifference(cv::Mat& mat1, cv::Mat mat2, bool contrast, const char* name, bool isBlackBack )
		{
			std::vector<cv::Mat> mat1chs, mat2chs;
			cv::split(mat1, mat1chs);
			cv::split(mat2, mat2chs);
	
			char str[256];
			for(int i=0; i<mat1.channels(); ++i)
			{
#pragma warning(push)
#pragma warning(disable:4996)
				sprintf(str, "%s difference %d", name, i);
#pragma warning(pop)
				cv::Mat dif = RedContritio::Experiment::ChannelDifference(mat1chs[i], mat2chs[i]);

				if(contrast)RedContritio::Experiment::Normalize(dif, dif);

				if(!isBlackBack)std::for_each(dif.begin<cv::Vec3b>(), dif.end<cv::Vec3b>(), [](cv::Vec3b& v){v[0] = ~v[0], v[1] = ~v[1], v[2] = ~v[2];});
				cv::imshow(str, dif);
			}
			return ;
		}


		void floodFill(cv::Mat img, cv::Point seedPoint, cv::Scalar newVal,
						cv::Rect* rect, cv::Scalar loDiff,cv::Scalar upDiff, int flags )
		{
			int wards[8][2] = {{1, 0},{-1, 0},{0, -1},{0, 1},{1, 1},{-1, -1},{1, -1}, {-1, 1}};
			int numOfWards = (flags&8)?8:4;
			cv::Mat vis = cv::Mat_<uchar>::zeros(img.size());

			auto loDif = OperationExpand::convert(loDiff);
			auto upDif = OperationExpand::convert(upDiff);

			typedef struct
			{
				int x, y;
				cv::Vec3b v;
			}_state;
			std::queue<_state> q;
			q.push({seedPoint.x, seedPoint.y, img.at<cv::Vec3b>(seedPoint.y, seedPoint.x)});
			vis.at<uchar>(seedPoint.y, seedPoint.x) = 1;

			cv::Vec3b fixed_point_v = img.at<cv::Vec3b>(seedPoint.y, seedPoint.x);
			bool use_fixed_v = flags&cv::FLOODFILL_FIXED_RANGE;

			while(!q.empty())
			{
				auto s = q.front();
				q.pop();
				if(use_fixed_v) s.v = fixed_point_v;
				for(int i=0; i<numOfWards; ++i)
				{
					/*printf("%d %d %d\n",!vis.at<uchar>(s.y+wards[i][0], s.x + wards[i][1]), 
						OperationExpand::operator<=(cv::Vec3b(s.v-loDif), img.at<cv::Vec3b>(s.y+wards[i][0], s.x + wards[i][1])),
						OperationExpand::operator>=(cv::Vec3b(s.v+upDif), img.at<cv::Vec3b>(s.y+wards[i][0], s.x + wards[i][1])));*/
					if(__LIMIT_POSITION(img,s.x + wards[i][1], s.y+wards[i][0]) 
					&&	!vis.at<uchar>(s.y+wards[i][0], s.x + wards[i][1])
					&& OperationExpand::operator<=(cv::Vec3b(s.v-loDif), img.at<cv::Vec3b>(s.y+wards[i][0], s.x + wards[i][1]))
					&& OperationExpand::operator>=(cv::Vec3b(s.v+upDif), img.at<cv::Vec3b>(s.y+wards[i][0], s.x + wards[i][1])))
					{
						q.push({s.x + wards[i][1], s.y+wards[i][0], img.at<cv::Vec3b>(s.y+wards[i][0], s.x + wards[i][1])});
						vis.at<uchar>(s.y+wards[i][0], s.x + wards[i][1]) = 1;
					}
				}
				img.at<cv::Vec3b>(s.y, s.x) = OperationExpand::convert(newVal);
			}
			img.at<cv::Vec3b>(seedPoint.y, seedPoint.x) = OperationExpand::convert(newVal);
		}
	}
}