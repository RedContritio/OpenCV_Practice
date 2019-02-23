#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>

#include <vector>

#include "_imgproc.h"

void FuckSHT(cv::Mat img);
void PPHT(cv::Mat img);
void CircleFind(cv::Mat img);
int main(void)
{
#ifdef LINE_AIM
	cv::Mat img = cv::imread("1.jpg");
	MatResize(img, *1/2);
	//FuckSHT(img); // just find line, not segement, because it can not find endpoint
	PPHT(img);
#else
	cv::Mat img = cv::imread("2.jpg");
	MatResize(img, *1/3);
	//CircleFind(img);
	PPHT(img);
#endif
	//cv::imshow("src", img);
	cv::waitKey();
	return 0;
}


void CircleFind(cv::Mat img)
{
	std::vector<cv::Vec3f> circles;
	cv::Mat gray, blur_, adthre, opened;
	cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
	cv::GaussianBlur(gray, blur_, cv::Size(15, 15), 0);
	cv::adaptiveThreshold(blur_, adthre, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);
	cv::morphologyEx(adthre, opened, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)), cv::Point(-1, -1), 2);
	cv::imshow("gray", gray);
	cv::imshow("blur", blur_);
	cv::imshow("adthre", adthre);
	cv::imshow("opened", opened);

	cv::Mat cirs(opened.size(), opened.type(), cv::Scalar(0));

	cv::HoughCircles(opened, circles, cv::HOUGH_GRADIENT, 1.5, 10, 200, 100, 10, 150);
	printf("hough end\n");
	for(auto it = circles.begin(); it != circles.end(); ++it)
	{
		cv::Point center((int)(*it)[0], (int)(*it)[1]);
		int radius = (int)(*it)[2];
		//cv::circle(cirs, center, 2, cv::Scalar(0xFF, 0xCC, 0x66), -1);
		cv::circle(cirs, center, radius, cv::Scalar(255), 2);
	}
	img.copyTo(cirs, cirs);
	cv::imshow("circles", cirs);
}

void PPHT(cv::Mat img)
{
	cv::Mat edge,_edge = img.clone();
	cv::GaussianBlur(_edge, _edge, cv::Size(15, 15), 0);
	imshow("_edge blur", _edge);
	//cv::blur(img, _edge, cv::Size(5, 5));
	//cv::GaussianBlur(img, _edge, cv::Size(3, 3), 0);
	cv::cvtColor(img, _edge, cv::COLOR_RGB2GRAY);
	cv::imshow("_edge convert", _edge);
	cv::adaptiveThreshold(_edge, _edge, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);
	cv::imshow("_edge adaptive threshold", _edge);
	cv::morphologyEx(_edge, _edge, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)), cv::Point(-1, -1), 2);
	cv::erode(_edge, _edge, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
	cv::imshow("_edge", _edge);
	edge = _edge;

	//cv::Canny(_edge, edge, 3, 9);
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edge, lines, 1, CV_PI/180, 80, 35, 10);
	cv::Mat lineimg(img.size(), img.type(), cv::Scalar(0));
	for(auto it = lines.begin(); it != lines.end(); ++it)
	{
		cv::Vec4i& v = *it;
		cv::line(lineimg, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), cv::Scalar(255, 255, 255), 2);
	}
	img.copyTo(lineimg, lineimg);
	//cv::addWeighted(img, 0.5, lineimg, 0.5, 0, lineimg);
	cv::imshow("edge", edge);
	cv::imshow("lines", lineimg);
	//cv::imwrite("3.jpg", lineimg);
}

void FuckSHT(cv::Mat img)
{
	cv::Mat edge,_edge;
	//cv::blur(img, _edge, cv::Size(5, 5));
	cv::GaussianBlur(img, _edge, cv::Size(15, 15), 0);
	cv::Canny(_edge, edge, 3, 9);

	std::vector<cv::Vec2f> lines;

	cv::HoughLines(edge, lines, 1, CV_PI/180, 150, 0, 0);
	cv::Mat lineimg(img.size(), img.type(), cv::Scalar::all(0));
	for(auto it = lines.begin(); it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		float ox = rho* cos(theta), oy = rho* sin(theta);
		cv::Point p1, p2;
		p1.x = cvRound(ox+ 100*(-sin(theta)));
		p2.x = cvRound(ox- 100*(-sin(theta)));
		p1.y = cvRound(oy+ 100*(cos(theta)));
		p2.y = cvRound(oy- 100*(cos(theta)));
		cv::line(lineimg, p1, p2, cv::Scalar(255, 255, 0));
	}
	cv::imshow("edge", edge);
	cv::imshow("lines", lineimg);
}