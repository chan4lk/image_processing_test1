#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>


void day1()
{
	IplImage *img = cvLoadImage("grass.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (!img)
	{
		std::cout << "Error: cannot open image";
		return;
	}

	int n = img->nChannels;		//Number of channels. Most OpenCV functions support 1-4 channels.
	int h = img->height;		//Image height in pixels
	int w = img->width;			//Image width in pixels
	int step = img->widthStep;	//The size of an aligned image row, in bytes.

	uchar *imgdata = (uchar *)img->imageData;

	int b = imgdata[0];
	int g = imgdata[1];
	int r = imgdata[2];

	printf("%d \n", step);
	printf("%d \n", w);
	printf("%d \n", h);

	printf("First Pixel Blue : %d \n", b);
	printf("First Pixel Green %d \n", g);
	printf("First Pixel Red %d \n", r);

	//display the image
	cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Image", img);

	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvReleaseImage(&img);

}