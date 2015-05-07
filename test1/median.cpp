#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv\cv.h>

using namespace cv;

/**
* @function main
*/
int median()
{

	Mat image = imread("grass.jpg");

	//kernal size
	//window size
	int const KERNEL_SIZE = 9;

	if (!image.data)
	{
		std::cout << "cannot open the image";
		waitKey(0);
	}

	Mat GrayImage(image.size(), CV_8UC1);

	cvtColor(image, GrayImage, CV_BGR2GRAY);

	Mat filteredImage(GrayImage.rows, GrayImage.cols, CV_8UC1);

	/*median filter*/

	//loop over image
	for (int i = 1; i < GrayImage.cols - 1; i++)
	{
		for (int j = 1; j < GrayImage.rows - 1; j++)
		{
			int windowValues[KERNEL_SIZE] = {};
			//loop over window
			int index = 0;
			for (int k = i - 1; k < i + 2; k++)
			{
				for (int l = j - 1; l < j + 2; l++)
				{

					windowValues[index] = (uchar)GrayImage.at<uchar>(l, k);
					index++;

				}
			}

			//sort array
			std::sort(windowValues, windowValues + KERNEL_SIZE);

			//replace window middle pixel with median value
			filteredImage.at<uchar>(j, i) = (uchar)windowValues[(KERNEL_SIZE + 1) / 2];

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