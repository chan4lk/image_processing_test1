#include "opencv\cv.h"
#include "opencv\cvaux.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;

int histogram(){
	Mat image = imread("grass.jpg");
	cvtColor(image, image, CV_BGR2GRAY);
	if (!image.data)
	{
		std::cout << "Cannot open the image";
		return -1;
	}

	int n = image.cols * image.rows;	//number of pixels
	int greylevels[256] = {};			//greylevel frequency	
	int m = 256;
	double Rk[256] = {};		//greylevel probabilities
	double Sk[256] = {};				//cummulative probabilities

	for (int i = 0; i < image.cols; i++)
	{
		for (int j = 0; j < image.rows; j++)
		{
			uchar pixelval = image.at<uchar>(j, i);
			greylevels[pixelval]++;
			Rk[pixelval] = (double)greylevels[pixelval] / n;
		}
	}

	//Sk[0] = greyLevelProb[0];
	//why Sk[k] = greyLevelProb[k] + Sk[k-1] dont work?
	/*for (int k = 0; k < 256; k++)
	{
	for (int p = 0; p < k; p++)
	{
	Sk[k] += Rk[p];
	}
	}*/

	Sk[0] = Rk[0];
	for (int k = 1; k < 256; k++)
	{
		Sk[k] = Rk[k] + Sk[k - 1];
	}

	for (int i = 0; i < image.cols; i++)
	{
		for (int j = 0; j < image.rows; j++)
		{
			uchar level = image.at<uchar>(j, i);
			uchar &pixelval = image.at<uchar>(j, i);
			pixelval = round(Sk[level] * m);
		}
	}

	namedWindow("image");
	imshow("image", image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}