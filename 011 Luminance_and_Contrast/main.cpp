#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <cstdio>

#define SCALE_RATE(x) x*4/9
const int sc_width = 1536;
const int sc_height = 864;

void onScroll(int , void*);

cv::Mat src, dst;
//ScrollBar *pluminance, *pcontrast;
int luminance = 100, contrast = 100;
const int countofluminance = 200, countofcontrast = 300;
const int luminancebias = luminance, contrastbias = contrast;
int main(int argc, char *argv[])
{

	src = cv::imread("1.jpg");
	cv::resize(src, src, cv::Size(SCALE_RATE(src.cols), SCALE_RATE(src.rows)));
	cv::imshow( "source", src);

	dst = src.clone();

	cv::namedWindow( "destination");
	cv::imshow("destination", dst);
	//ScrollBar* pluminance = new ScrollBar("Luminance", "destination", 80, 200, onScroll);
	//ScrollBar* pcontrast = new ScrollBar("Contrast", "destination", 80, 300, onScroll);
	
	cv::createTrackbar("Luminance", "destination", &luminance, countofluminance, onScroll);
	onScroll(luminance, 0);
	
	cv::createTrackbar("Contrast", "destination", &contrast, countofcontrast, onScroll);
	onScroll(contrast, 0);

	while(char(cv::waitKey()) != ' ');
	return 0;
}


void onScroll(int , void*)
{
	printf("on scroll\n");
	for(int i=0; i<src.rows; i++)
	{
		for(int j=0; j<src.cols; j++)
		{
			for(int k=0; k<src.channels(); k++)
			{
				dst.at<cv::Vec3b>(i, j)[k] = cv::saturate_cast<uchar>((255*1.0*(luminance-luminancebias)/countofluminance)+ 
											src.at<cv::Vec3b>(i,j)[k] * ( 1 +3.0* (contrast-contrastbias)/ countofcontrast));
			}
		}
	}
	cv::imshow("destination", dst);
	cv::imshow( "source", src);
}