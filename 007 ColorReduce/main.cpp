#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include "ColorReduce.h"

#define COLOR_REDUCE(src,dst,methodselector) do{ cv::Mat dst;\
												 ColorReduce<methodselector>( src, dst);\
												 cv::imshow( CR_METHOD_NAME[methodselector]+4, dst);\
												}while(0);

int main( void)
{
	cv::Mat img = cv::imread( "small.png");
	cv::imshow( "src", img);
	img.resize(img.cols/2, img.rows/2);

	COLOR_REDUCE( img, dst, CRM_LOOKUPTABLE);
	COLOR_REDUCE( img, dst, CRM_DIV);
	COLOR_REDUCE( img, dst, CRM_ITERATOR);
	COLOR_REDUCE( img, dst, CRM_ATDIV);
	COLOR_REDUCE( img, dst, CRM_ALLCHANNELS);

	cv::waitKey( 0);
}