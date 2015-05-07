#include "opencv\cv.h"
#include "opencv\cvaux.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;

int day3(){
	Mat image = imread("day2.jpg");
	Mat image2 = imread("grass.jpg");

	if (!image.data){
		printf("Could not open or find image!");
		waitKey(0);
		return -1;
	}

	if (!image2.data){
		printf("Could not open or find image!");
		waitKey(0);
		return -1;
	}

	//print image details
	printf("image width: %d\n", image.cols);
	printf("image height: %d\n", image.rows);
	printf("image width step: %d\n", image.step);
	printf("image channels: %d\n", image.channels());

	//access pixel
	Vec3b pixel = image.at<Vec3b>(10, 10);
	printf("blue: %d\n", pixel.val[0]);
	printf("green: %d\n", pixel.val[1]);
	printf("red: %d\n", pixel.val[2]);

	//make range white
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			Vec3b &intensity = image.at<Vec3b>(j, i);
			for (int k = 0; k < image.channels(); k++) {
				// change pixel value for all three channels
				intensity.val[k] = 255;
			}
		}
	}

	//replace image part
	for (int i = 100; i < 200; i++) {
		for (int j = 100; j < 200; j++) {
			Vec3b &intensity = image.at<Vec3b>(j, i);
			Vec3b &intensity2 = image2.at<Vec3b>(j, i);
			//pixel can be copied entirely without copying bgr values one by one
			intensity2 = intensity;
			/*for(int k = 0; k < image.channels(); k++) {
			intensity2.val[k] = intensity.val[k];
			}*/
		}
	}

	//convert to grayscale image
	Mat grayimage1(image.size(), CV_8U);

	//using inbuilt method
	cvtColor(image, grayimage1, CV_BGR2GRAY);
	//binaryimage1 > 128;

	//manual
	/*for (int i = 0; i < image.cols; i++) {
	for (int j = 0; j < image.rows; j++) {
	Vec3b pixel = image.at<Vec3b>(j, i);
	uchar &pixel2 = grayimage1.at<uchar>(j, i);
	pixel2 = uchar (0.299 * pixel.val[0] + 0.587 * pixel.val[1] + 0.115 * pixel.val[2]);
	}
	}*/

	//negative image
	/*Mat negativeimage(image.size(), image.depth());
	for (int i = 0; i < image.cols; i++) {
	for (int j = 0; j < image.rows; j++) {
	Vec3b pixel = image.at<Vec3b>(j, i);
	Vec3b &pixel2 = negativeimage.at<Vec3b>(j, i);
	/*pixel2.val[0] = pixel.val[0] - 255;
	pixel2.val[1] = pixel.val[1] - 255;
	pixel2.val[2] = pixel.val[2] - 255;
	}
	}

	//cvtColor(image, negativeimage, CV_inverse

	namedWindow("negativepenguins");
	imshow("negativepenguins", negativeimage);*/

	//histogram
	int grayvalues[256] = {};

	for (int i = 0; i < grayimage1.cols; i++) {
		for (int j = 0; j < grayimage1.rows; j++) {
			int pixel = grayimage1.at<uchar>(j, i);
			grayvalues[pixel]++;
		}
	}

	printf("histogram\n");

	for (int i = 0; i < 256; i++)
	{
		printf("%d: %d\n", i, grayvalues[i]);
	}

	//drawing graphical histogram
	double max = 10519;
	Mat histimage(500, 256, CV_8UC1, Scalar(255));

	//normalizing
	int hist[256] = {};
	for (int i = 0; i < 256; i++) {
		hist[i] = cvRound(grayvalues[i] / max * 500);
		line(histimage, Point(i, 500 - hist[i]),
			Point(i, 500), Scalar(0), 1, 8, 0);
	}
	//bin_w = cvRound (histogram_cols / 256);

	namedWindow("histogram");
	imshow("histogram", histimage);


	//contrast stretching
	for (int i = 0; i < grayimage1.cols; i++) {
		for (int j = 0; j < grayimage1.rows; j++) {
			int px = grayimage1.at<uchar>(j, i);
			if (px < 150)
			{
				grayimage1.at<uchar>(j, i) = 0;
			}
			else
			{
				if (px >= 150 && px < 220)
				{
					grayimage1.at<uchar>(j, i) = uchar((px - 10) * 3.4 + 10);
				}
				else
				{
					grayimage1.at<uchar>(j, i) = uchar((px - 220) * 0.14 + 250);
				}
			}
		}
	}

	namedWindow("binarypenguins");
	imshow("binarypenguins", grayimage1);

	namedWindow("penguins");
	imshow("penguins", image);

	namedWindow("jellyfish");
	imshow("jellyfish", image2);

	waitKey(0);

	destroyWindow("penguins");
	destroyWindow("jellyfish");
	destroyWindow("binarypenguins");
	destroyWindow("negativepenguins");
	destroyWindow("histogram");
	return 0;
}