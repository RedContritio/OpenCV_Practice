#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#define SCALE_RATE(x) x*1/2
const int sc_width = 1536;
const int sc_height = 864;

int main(int argc, char *argv[])
{
	cv::Mat src = cv::imread("1.jpg", 0);
	cv::resize(src, src, cv::Size(SCALE_RATE(src.cols), SCALE_RATE(src.rows)));
	cv::imshow("source",src);
	
	int m = cv::getOptimalDFTSize(src.rows);
	int n = cv::getOptimalDFTSize(src.cols);
	cv::Mat padded;
	cv::copyMakeBorder(src, padded, 0, m-src.rows, 0, n-src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
	cv::Mat ComplexI;
	cv::merge(planes, 2, ComplexI);
	cv::dft(ComplexI, ComplexI);

	cv::split(ComplexI, planes);

	cv::Mat magnitudeImg;
	cv::magnitude(planes[0], planes[1], magnitudeImg);
	magnitudeImg += cv::Scalar::all(1);
	cv::log(magnitudeImg, magnitudeImg);

	magnitudeImg = magnitudeImg(cv::Rect(0, 0, magnitudeImg.cols & (-2), magnitudeImg.rows & (-2)));
	int cx = magnitudeImg.cols/2;
	int cy = magnitudeImg.rows/2;
	cv::Mat Quadrants[2][2];
	for(int i=0; i<2; ++i)
		for(int j=0; j<2; ++j)
			Quadrants[i][j] = cv::Mat(magnitudeImg, cv::Rect(j*cx, i*cy, cx, cy));

	/*
	cv::Mat tmp;
	Quadrants[0][0].copyTo(tmp);
	Quadrants[1][1].copyTo(Quadrants[0][0]);
	tmp.copyTo(Quadrants[1][1]);

	Quadrants[0][1].copyTo(tmp);
	Quadrants[1][0].copyTo(Quadrants[0][1]);
	tmp.copyTo(Quadrants[1][0]);
	*/

	cv::normalize(magnitudeImg, magnitudeImg, 0, 1, cv::NORM_MINMAX);
	cv::imshow("Frequency", magnitudeImg);

	cv::waitKey();
	return 0;
}