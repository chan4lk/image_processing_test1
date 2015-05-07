#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv\cv.h>

using namespace cv;

/**
* @Mean Filter
*/
int mean()
{

	Mat image = imread("grass.jpg");


	if (!image.data){
		printf("Could not open or find image!");
		waitKey(0);
		return -1;
	}

	//convert to grayscale image
	Mat GrayImage(image.size(), CV_8U);

	//using inbuilt method
	cvtColor(image, GrayImage, CV_BGR2GRAY);


	namedWindow("NoisyImage");
	imshow("NoisyImage", GrayImage);


	Mat  kernel(3, 3, CV_32FC1);

	for (int k = 0; k<kernel.cols; k++){
		for (int l = 0; l<kernel.rows; l++){
			kernel.at<float>(l, k) = (float)(1 / 9.0);
		}
	}

	Mat filteredImage(GrayImage.rows, GrayImage.cols, CV_8UC1);
	// mean filtering

	int x;
	int y;
	int k;
	int j;


	for (x = 1; x < GrayImage.cols - 1; x++){
		for (y = 1; y < GrayImage.rows - 1; y++){
			float sum_3x3 = 0.0;
			for (k = -1; k <= 1; k++){
				for (j = -1; j <= 1; j++){
					sum_3x3 += kernel.at<float>(k + 1, j + 1) * GrayImage.at<uchar>(y + k, x + j);
				}
			}
			filteredImage.at<uchar>(y, x) = (uchar)sum_3x3;
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