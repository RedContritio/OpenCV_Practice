#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include "imgproc_.h"

#include <iostream>


void ScaleInterTest(cv::Mat& img, int interateGeneration = 1, int interpolation = cv::INTER_LINEAR );

#define ScaleTestMacro(generation,interpolation) do{cv::Mat dst = img.clone();\
													ScaleInterTest(dst, generation,interpolation);\
													cv::imshow("Pry " #generation " " #interpolation, dst);} while (0);

int main(void)
{
	cv::Mat img = cv::imread("1.jpg");
	resize(img, img, img.size()/2);
	cv::imshow("", img);

	cv::Mat p, p2;
	
	cv::pyrDown(img, p);
	for(int i=0; i<5; i++) cv::pyrDown(p, p);
	//cv::imshow("pyrDown", p);
	//cv::pyrUp(img, p);
	for(int i=0; i<6; i++) cv::pyrUp(p, p);
	cv::resize(p, p, img.size());
	cv::imshow("pyr", p);
	
	cv::Mat tmp = p-img;
	cv::imshow("pyr - src", tmp);
	RedContritio::Experiment::inverseColor(tmp,tmp);
	cv::imshow("inv pyr - src", tmp);

	tmp = img - p;
	cv::imshow("src - pyr", tmp);
	RedContritio::Experiment::inverseColor(tmp,tmp);
	cv::imshow("inv src - pyr", tmp);
	
	//RedContritio::Experiment::MatDifference(p, p2);
	//printf("Equal? %d\n",RedContritio::Experiment::operator==(p, p2));


	
	RedContritio::Experiment::pyrDown(img, p2);
	for(int i=0; i<5; i++) RedContritio::Experiment::pyrDown(p2, p2);
	//cv::imshow("pyrDown reco", p2);
	//RedContritio::Experiment::pyrUp(img, p2);
	for(int i=0; i<6; i++) RedContritio::Experiment::pyrUp(p2, p2);
	cv::resize(p2, p2, img.size());
	cv::imshow("pyr reco", p2);

	//ScaleTestMacro(6,0)
	//ScaleTestMacro(6,1)
	//ScaleTestMacro(6,2)
	//ScaleTestMacro(6,3)
	//ScaleTestMacro(6,4)
	//ScaleTestMacro(6,5)


	cv::waitKey();
	return 0;
}

void ScaleInterTest(cv::Mat& img, int interateGeneration, int interpolation)
{
	cv::Size sz = img.size();
	resize(img, img, sz/2, 0, 0, interpolation);
	if(interateGeneration > 1)ScaleInterTest(img, interateGeneration-1, interpolation);
	resize(img, img, sz, 0, 0, interpolation);
}