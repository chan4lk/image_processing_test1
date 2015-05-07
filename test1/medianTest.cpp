#include<opencv\cv.h>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace cv;

int medianTest()
{
	Mat image = imread("grass.jpg");

	if (!image.data)
	{
		printf("Unable to load image. exiting...");
		waitKey(0);
		return -1;			
	}

	int const KERNAL_SIZE = 9;

	Mat grayImage(image.size(), CV_8UC1);

	cvtColor(image, grayImage, CV_BGR2GRAY);

	Mat filteredImage(grayImage.rows, grayImage.cols, CV_8UC1);

	for (int i = 1; i < grayImage.cols - 1; i++)
	{
		for (int j = 1; j < grayImage.rows -1 ; j++)
		{
			int windowValues[KERNAL_SIZE] = {};

			int index = 0;

			for (int k = i -1; k < i +2 ; k++)
			{
				for (int l = j - 1; l < j + 2; l++)
				{
					windowValues[index] = (uchar)grayImage.at<uchar>(l, k);
					index++;
				}
			}

			std::sort(windowValues, windowValues + KERNAL_SIZE);

			filteredImage.at<uchar>(j, i) = (uchar)windowValues[(KERNAL_SIZE + 1) / 2];
		}
	}

	namedWindow("original", 0);
	imshow("original", grayImage);

	waitKey(0);

	namedWindow("median filtered", 0);
	imshow("median filtered", filteredImage);

	waitKey(0);

	return 0;
}
