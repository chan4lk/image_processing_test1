#include "opencv\cv.h"
#include "opencv\cvaux.h"
#include "opencv\highgui.h"

using namespace cv;

int day2(){
	Mat image = imread("grass.jpg");
	Mat image2 = imread("day2.jpg");

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
	Vec3b pixel = image.at<Vec3b>(10, 1000);
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
	//cvtColor(image, binaryimage1, CV_BGR2GRAY);
	//binaryimage1 > 128;

	//manual
	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			Vec3b pixel = image.at<Vec3b>(j, i);
			uchar &pixel2 = grayimage1.at<uchar>(j, i);
			pixel2 = uchar(0.299 * pixel.val[0] + 0.587 * pixel.val[1] + 0.115 * pixel.val[2]);
		}
	}

	//negative image
	Mat negativeimage(image.size(), image.type());
	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			Vec3b pixel = image.at<Vec3b>(j, i);
			Vec3b &pixel2 = negativeimage.at<Vec3b>(j, i);
			pixel2.val[0] = 255 - pixel.val[0];
			pixel2.val[1] = 255 - pixel.val[1];
			pixel2.val[2] = 255 - pixel.val[2];
		}
	}

	namedWindow("negativepenguins");
	imshow("negativepenguins", negativeimage);

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
	return 0;
}