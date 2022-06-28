#include <opencv2/opencv.hpp> 
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

#define pi 3.1415926


void Rotate(const Mat &srcImage, Mat &destImage, double angle);

int main(int argc,char** argv)
{
	Mat img = imread("bennu.jpg", IMREAD_GRAYSCALE);
	//Mat img = imread("input12.png", IMREAD_GRAYSCALE);

	float x = 0.05, y=0.5,z = 3.27;


	//printf("\n %d  %d", img.cols, img.rows);
	//printf("\n %d \n", img.channels());

	int r = min(img.cols, img.rows)/2;

	int midrow = (int)img.rows/2;
	int midcol = (int)img.cols/2;

	int times = 0;

///////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		times++;
		Mat outimg(img.size(), img.type(), Scalar(0));
		float zz = times * z;
		float cosz = cos(zz * pi /180.0);
		float sinz = sin(zz * pi /180.0);
		float ratio = 1-cosz; ///////////////////////

		for (int row  = 0; row  < img.rows; row ++)
		{
			uchar* imgdata = img.ptr<uchar>(row);
			uchar* outdata = outimg.ptr<uchar>(row);
			int d = abs(row - midrow);

			float rx = (float)r*r - d*d;

			float r1 = (float)sqrt(r*r - d*d);
			int offset = (int)r1 * ratio;//////////////////
			float ofet = r1 * ratio;

			for (int col  = 0; col  < img.cols; col ++)
			{
				ofet = ofet * cos(abs(col - midcol));
				int ncol = col+offset;

				//if(ncol >= midcol+rx || ncol<=midcol-rx)
				//	continue;
				if(ncol >= img.cols || ncol<0)
					continue;

				outdata[ncol] = imgdata[col];
			}
		}
		//Rotate(outimg, outimg, times * x);
		imshow("out", outimg);	
		//imwrite("16ddu.jpg", outimg);
		waitKey(0);
	}

///////////////////////////////////////////////////////////////////////////////////
	while(0)
	{
		times++;
		Mat outimg(img.size(), img.type(), Scalar(0));
		float zz = times * z;
		float cosz = cos(zz * pi /180.0);
		float sinz = sin(zz * pi /180.0);
		//float ratio = 1-cosz; ///////////////////////

		for (int row  = 0; row  < img.rows; row ++)
		{
			uchar* imgdata = img.ptr<uchar>(row);
			uchar* outdata = outimg.ptr<uchar>(row);
			int d = abs(row - midrow);

			float rx = (float)r*r - d*d;

			//float r1 = (float)sqrt(r*r - d*d);
			//int offset = (int)r1 * ratio;//////////////////

			for (int col  = 0; col  < img.cols; col ++)
			{

				int dx = abs(col - midcol);
				int ofet = (int)dx*(1-cosz) + sqrt(rx-dx*dx)*sinz;

				int ncol = col+ofet;

				if(ncol >= midcol+rx || ncol<=midcol-rx)
					continue;
				//if(ncol >= img.cols || ncol<0)
				//	continue;

				outdata[ncol] = imgdata[col];
			}
		}
		//Rotate(outimg, outimg, times * x);
		imshow("out", outimg);	
		//imwrite("16ddu.jpg", outimg);
		waitKey(0);
	}

}


void Rotate(const Mat &srcImage, Mat &destImage, double angle)
{
	Point2f center(srcImage.cols / 2, srcImage.rows / 2);//中心
	Mat M = getRotationMatrix2D(center, angle, 1);//计算旋转的仿射变换矩阵 
	warpAffine(srcImage, destImage, M, Size(srcImage.cols, srcImage.rows));//仿射变换  
	circle(destImage, center, 2, Scalar(255, 0, 0));
}
