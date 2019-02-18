#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <vector>
#include <cstdio>

#define SCALE_RATE(x) x*2/9
const int sc_width = 1536;
const int sc_height = 864;

void MatFill(cv::Mat& img);
void ShowSingleChannel(cv::Mat channel, int id, int x, int y);

cv::Mat img;
int main(void)
{
	img = cv::imread("1.jpg");
	cv::resize(img, img, cv::Size(SCALE_RATE(img.cols), SCALE_RATE(img.rows)));
	cv::imshow("img", img);
	cv::moveWindow("img", 0, 0);

	std::vector<cv::Mat> channels;
	cv::split(img, channels);
	
	for(int i=0; i<channels.size(); i++)
	{
		ShowSingleChannel(channels[i], i, (i+1)*sc_width/4, 0);
	}

	cv::Mat merged;

	cv::merge(channels, merged);
	//cv::imshow("merge", merged);
	cv::waitKey();
	return 0;
}


void MatFill(cv::Mat& img)
{
	cv::Mat LookUpTable( 1, 0x100, CV_8U);
	uchar *p = LookUpTable.data;
	for( int i=0; i<0x100; i++) p[i] = 0;
	cv::LUT( img, LookUpTable, img);
}


void ShowSingleChannel(cv::Mat channel, int id, int x, int y)
{
	char s[20] = {};

	cv::Mat BlackPic = channel.clone();
	MatFill(BlackPic);

	std::vector<cv::Mat> blackchannels = {BlackPic, BlackPic, BlackPic};

	blackchannels[id] = channel;
	
#pragma warning(push)
#pragma warning(disable:4996)
	sprintf(s, "Channel %d\n", id);
#pragma warning(pop)

	cv::Mat newpic;
	cv::merge(blackchannels, newpic);
	cv::imshow(s, newpic);
	cv::moveWindow(s, x, y);
}