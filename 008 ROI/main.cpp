#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <iostream>
#include "ROI.h"

#define ROI_PTR(name, pic) try{\
								cv::imshow(name, pic);\
								}\
						   catch(cv::Exception e)\
							{\
								std::cout<< "Exception Caught in "<< name<< " : "<< e.msg;\
								}
#define ROI_FULL(src, dst, name, region, method) do{ cv::Mat dst;\
													 _ROI<method>(src, dst, region);\
													 ROI_PTR(name, dst);\
													}while(0);
#define ROI(src, region, method) ROI_FULL(src, src##_ROI_##method, "ROI_" #method, region, method)

int main( void)
{
	cv::Mat img = cv::imread( "small.png");
	cv::Exception e;
	try
	{
		cv::imshow( "src", img);
	}
	catch(cv::Exception e)
	{
		std::cout<<e.msg;
	}

	cv::Rect region(200, 300, 400, 200);
	ROI(img, region, 0);
	ROI(img, region, 1);
	ROI(img, region, 2);

	cv::waitKey();

}

