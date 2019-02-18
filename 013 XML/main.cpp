#include <core/core.hpp>
#include <opencv.hpp>
#include <iostream>

int getRandomInteger(void);

void FileWriteTest(void);
int main(int argc, char *argv[])
{
	FileWriteTest();
	return 0;
}

void FileWriteTest(void)
{
#define __IS_XML 1
#define SUFFIX "yaml"

#if __IS_XML
	#undef SUFFIX
	#define SUFFIX "xml"
#endif

	try
	{
		cv::FileStorage fs("test." SUFFIX, cv::FileStorage::WRITE);

	#if __IS_XML
		fs << "test_id" << 2333; // it's not allowed to exist a blank in the key name
	#else
		fs << "test id" << 2333;
	#endif
		cv::Mat CameraMatrix = (cv::Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
		fs << "CameraMatrix" << CameraMatrix;

		fs << "RandomInteger" << "[";
		for(int i=0; i<10; i++)
		{
			fs << "{:" << "x" << getRandomInteger()%200 << "y" << getRandomInteger()%200 << "value" << "[:";
			for(int j=0; j<9; j++)
			{
				fs << getRandomInteger()%200;
			}
			fs << "]" << "}";
		}
		fs << "]";
	}
	catch(cv::Exception e)
	{
		std::cout<< "EXP"<< std::endl
			<< e.msg<< std::endl;
		system("pause");
	}
	return ;
}


int getRandomInteger(void)
{
	static int vinit = 2333333;
	static int vfact = 114514;
	static int vplus = 700000;
	static int vmoder = 3424867;
	
	vinit = vinit * vfact + vplus;
	if(vinit < 0 ) vinit = -(vinit+1);
	vfact ++;
	vplus --;
	return vinit%vmoder;
}