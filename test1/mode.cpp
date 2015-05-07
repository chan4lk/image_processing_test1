#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv\cv.h>

using namespace cv;
using namespace std;
/**
*  Mode Filtering
*/

int findTheMode(int array[], int size);

int mode()
{

	Mat image = imread("grass.jpg");

	int const KERNEL_SIZE = 9;

	if (!image.data)
	{
		std::cout << "cannot open the image";
		waitKey(0);
	}

	Mat GrayImage(image.size(), CV_8UC1);

	cvtColor(image, GrayImage, CV_BGR2GRAY);

	Mat filteredImage(GrayImage.rows, GrayImage.cols, CV_8UC1);


	for (int i = 1; i < GrayImage.cols - 1; i++)
	{
		for (int j = 1; j < GrayImage.rows - 1; j++)
		{
			int windowValues[KERNEL_SIZE] = {};

			int index = 0;
			for (int k = i - 1; k < i + 2; k++)
			{
				for (int l = j - 1; l < j + 2; l++)
				{

					windowValues[index] = (uchar)GrayImage.at<uchar>(l, k);
					index++;

				}
			}


			std::sort(windowValues, windowValues + KERNEL_SIZE);

			int modeVlaue = findTheMode(windowValues, KERNEL_SIZE);

			filteredImage.at<uchar>(j, i) = (uchar)modeVlaue;

		}
	}

	namedWindow("original");
	imshow("original", GrayImage);
	namedWindow("medianfilter");
	imshow("medianfilter", filteredImage);
	waitKey(0);
	destroyAllWindows();

	return 0;

}

int findTheMode(int kernelValues[], int size){
	int num = kernelValues[0];
	int mode = num;
	int count = 1;
	int modeCount = 1;

	for (int i = 1; i< size; i++)
	{
		if (kernelValues[i] == num)
		{
			modeCount++;
		}
		else
		{
			if (count < modeCount)
			{
				modeCount = count;
				mode = num;
			}
			count = 1;
			num = kernelValues[i];
		}
	}
	return mode;
}