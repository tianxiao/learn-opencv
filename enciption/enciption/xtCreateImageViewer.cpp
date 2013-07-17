#include "StdAfx.h"
#include "xtCreateImageViewer.h"
#include <opencv2/opencv.hpp>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

xtCreateImageViewer::xtCreateImageViewer(void)
{
}


xtCreateImageViewer::~xtCreateImageViewer(void)
{
}

void xtCreateImageViewer::LoadDisplayImage()
{
	IplImage *img = cvLoadImage( "./mike_klay_closing_in.jpg" );
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Exaple1", img );
	cvWaitKey(0);
	cvReleaseImage( &img );
	cvDestroyWindow( "Example1" );
}

void xtCreateImageViewer::LoadDisplaySmoothImage()
{
	IplImage *img = cvLoadImage( "./mike_klay_closing_in.jpg" );
	cvNamedWindow( "Exmaple4-in" );
	cvNamedWindow( "Example4-out" );

	cvShowImage( "Example4-in", img );

	IplImage *out = cvCreateImage(
		cvGetSize( img ),
		IPL_DEPTH_8U,
		3
		);

	// kernel window should be odd. 
	cvSmooth( img, out, CV_GAUSSIAN, 91, 91 );

	cvShowImage( "Example4-out", out );

	cvReleaseImage( &out );

	cvWaitKey( 0 );
	cvDestroyWindow( "Example4-in" );
	cvDestroyWindow( "Example4-out" );

}

void xtCreateImageViewer::LoadDisplayResizeImage()
{
	IplImage *img = cvLoadImage( "./mike_klay_closing_in.jpg" );
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Downsizebyhalf", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Exaple1", img );
	

	assert( img->width%2==0 && img->height%2==0 );

	IplImage *out = cvCreateImage(
		cvSize( img->width/2, img->height/2 ),
		img->depth,
		img->nChannels);

	cvPyrDown( img, out );
	
	cvShowImage( "Downsizebyhalf", out );

	cvReleaseImage( &img );
	cvWaitKey(0);
	cvDestroyWindow( "Example1" );
	cvDestroyWindow( "Downsizebyhalf" );
}

void xtCreateImageViewer::LoadDisplaCannyProcess()
{
	IplImage *img = cvLoadImage( "./fruits.jpg" );
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Downsizebyhalf", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Exaple1", img );
	
	IplImage *cedge = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,3);
	IplImage *cgray = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	IplImage *edge = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);
	cvCvtColor(img, cgray, CV_BGR2GRAY);
	cvSmooth( cgray, edge, CV_BLUR, 3, 3, 0, 0);
	cvNot( cgray, edge );
	IplImage *out = DoCanny( edge,10.,100.,3. );

	
	cvZero( cedge );
	cvCopy( img, cedge, out);


	

	//cvPyrDown( img, out );
	
	cvShowImage( "Downsizebyhalf", cedge );

	cvReleaseImage( &img );
	cvWaitKey(0);
	cvDestroyWindow( "Example1" );
	cvDestroyWindow( "Downsizebyhalf" );
}

IplImage* xtCreateImageViewer::DoCanny(IplImage *in, double lowThresh, double highThresh, double aperture)
{
	if ( in->nChannels !=1 ) 
		return NULL; // Canny only handles gray scale images

	IplImage *out = cvCreateImage(
		cvGetSize( in ) ,
		IPL_DEPTH_8U,
		1
		);

	cvCanny( in, out, lowThresh, highThresh, (int)aperture );
	return out;
}

void xtCreateImageViewer::LoadROIImage()
{
	IplImage *img = cvLoadImage( "./mike_klay_closing_in.jpg" );
	cvNamedWindow( "Example", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Downsizebyhalf", CV_WINDOW_AUTOSIZE );
	cvShowImage( "Exaple1", img );
	
	double aspectRatio = 1.*img->width/img->height;
	int ll = 640;
	int x = 20;
	int y = 40;
	int add = 50;
	int width = ll;
	int height = (int)(ll*aspectRatio);
	cvSetImageROI(img, cvRect(x,y,width,height));
	cvAddS(img, cvScalar(add),img);
	cvResetImageROI(img);
	
	

	assert( img->width%2==0 && img->height%2==0 );

	IplImage *out = cvCreateImage(
		cvSize( img->width/2, img->height/2 ),
		img->depth,
		img->nChannels);

	cvPyrDown( img, out );
	
	cvShowImage( "Downsizebyhalf", out );

	cvReleaseImage( &img );
	cvWaitKey(0);
	cvDestroyWindow( "Example1" );
	cvDestroyWindow( "Downsizebyhalf" );
}

void xtCreateImageViewer::LoadROIImage(int arv, char *argv[])
{
	IplImage *src;
	if ( arv == 7 && ( (src=cvLoadImage(argv[1],1))!=0 ) ) {
		int x = atoi(argv[2]);
		int y = atoi(argv[3]);
		int width = atoi(argv[4]);
		int height = atoi(argv[5]);
		int add = atoi(argv[6]);
		cvSetImageROI(src, cvRect(x,y,width,height));
		cvAddS(src, cvScalar(add), src);
		cvResetImageROI(src);
		cvNamedWindow( "Roi_Add", 1);
		cvShowImage( "Roi_Add", src );
		cvWaitKey(0);
	}

}

void SetColorImageToGray(IplImage *src, IplImage *dest, double redpercent, double greenpercent, double bluepercent)
{
	for ( int h=0; h<src->height; ++h ) {
		for ( int w=0; w<src->width; ++w ) {
			src->imageData[3*(h*src->width + w)] = 
				src->imageData[3*(h*src->width + w)]*redpercent +
				src->imageData[3*(h*src->width + w)+1]*greenpercent +
				src->imageData[3*(h*src->width + w)+2]*bluepercent;
		}
	}
}

void SetColorImageToSelf(IplImage *src)
{
	for ( int row=0; row<src->height; ++row ) {
		for ( int col=0; col<src->width; ++col ) {
			int pos = src->nChannels*(src->width*row+col);
			src->imageData[pos] = src->imageData[pos]+150;
			src->imageData[pos] = src->imageData[pos];
			src->imageData[pos] = src->imageData[pos];
		}
	}
}

void SetColorImageToGray(IplImage *src, IplImage *des)
{
	assert(src->width==des->width&&src->height==des->height);
	assert(des->nChannels==1);
	assert(src->nChannels==3);
	for ( int row=0; row<src->height; ++row ) {
		for ( int col=0; col<src->width; ++col ) {
			int pos = src->nChannels*(src->width*row+col);
			int posgray  = des->nChannels*(des->width*row+col);
			des->imageData[posgray] = 
				src->imageData[pos]*0.1 +
				src->imageData[pos+1]*0.60 +
				src->imageData[pos+2]*0.3;
		}
	}
}


void xtCreateImageViewer::ConvertImageToGray(int arv, char *argv[])
{
	/****
	myimage.imageData[3*(y*myimage.width+x)+0] = 100; //Red
	myimage.imageData[3*(y*myimage.width+x)+1] = 100; //Green
	myimage.imageData[3*(y*myimage.width+x)+2] = 100; //Blue
	****/


	IplImage *src;
	if ( arv==5 && ( (src=cvLoadImage(argv[1]))!=0) ) {
		double redpercen = atof(argv[2]);
		double greenpercen = atof(argv[3]);
		double bluepercen = atof(argv[4]);
		double sum = redpercen + greenpercen + bluepercen;
		redpercen/=sum;
		greenpercen/=sum;
		bluepercen/=sum;

		IplImage *gray = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
		//cvCvtColor( src, gray, CV_BGR2GRAY );

		//SetColorImageToGray(src,gray,redpercen,greenpercen,bluepercen);
		//use the IplImage==============================================
		FILE *fp = fopen("gray3.ppm","w");

		fprintf(fp,"P3\n");
		fprintf(fp,"%d %d\n",src->width,src->height);
		fprintf(fp,"%d\n",15);
		for ( int h=0; h<src->height; ++h ) {
			for ( int w=0; w<src->width; ++w ) {
				//cv::Mat image;
				//image.at<cv::Vec3b>(

				int pos = src->nChannels*(h*src->width+w);
				fprintf(fp,"%d %d %d\n",
					(unsigned char)src->imageData[pos],
					(unsigned char)src->imageData[pos+1],
					(unsigned char)src->imageData[pos+2]);
			}
		}

		fclose(fp);
		//===============================================================

		//use Mat========================================================
		FILE *fp2 = fopen("gray3.ppm","w");
		cv::Mat matImg(src);
		for ( int h=0; h<matImg.cols; ++h ) {
			for ( int w=0; w<matImg.rows; ++w ) {
				int red = matImg.at<cv::Vec3b>(h,w)[0];
				int green = matImg.at<cv::Vec3b>(h,w)[1];
				int blue = matImg.at<cv::Vec3b>(h,w)[2];
				fprintf(fp2,"%d %d %d\n",red,green,blue);
			}
		}
		fclose(fp2);
		//===============================================================

		char savegray[100];
		strcpy(savegray,argv[1]);
		
		cvSaveImage( "gray.jpg", src);
	}
}

/****
http://stackoverflow.com/questions/8932893/accessing-certain-pixel-rgb-value-in-opencv
cv::Mat image = ...do some stuff...;

image.at<cv::Vec3b>(y,x); gives you the RGB (it might be ordered as BGR) vector of type cv::Vec3b

image.at<cv::Vec3b>(y,x)[0] = newval[0];
image.at<cv::Vec3b>(y,x)[1] = newval[1];
image.at<cv::Vec3b>(y,x)[2] = newval[2];
****/
void xtCreateImageViewer::DumpToPPM()
{
	//for ( int i=0; i<1000; ++i ) {
	IplImage *src = cvLoadImage("mike_klay_closing_in.jpg");
	
	cvSaveImage( "milksky.bmp", src );

	//OverSaveBMPFile();
	//src = cvLoadImage("milksky.bmp");
	cv::Mat imgmat(src);

	cvSave( "my_image.xml", src);
	//=====================================================================
	FILE *fp = fopen("fruits.ppm","w");
	fprintf(fp,"P3\n");
	fprintf(fp,"%d %d\n",src->width,src->height);
	fprintf(fp,"%d\n",15);
	//for ( int i=0; i<imgmat.cols; ++i) {
	//	for ( int j=0; j<imgmat.rows; ++j ) {
	//		int red = imgmat.at<cv::Vec3b>(j,i)[0];
	//		int gre = imgmat.at<cv::Vec3b>(j,i)[1];
	//		int blu = imgmat.at<cv::Vec3b>(j,i)[2];
	//		fprintf(fp,"%d %d %d\n",red,gre,blu);
	//	}
	//}

	
	for ( int i=0; i<imgmat.rows; ++i ) {
		for ( int j=0; j<imgmat.cols; ++j ) {
			//int red = imgmat.at<cv::Vec3b>(i,j)[0];
			//int gre = imgmat.at<cv::Vec3b>(i,j)[1];
			//int blu = imgmat.at<cv::Vec3b>(i,j)[2];
			int red = imgmat.at<cv::Vec3b>(i,j)[2];
			int gre = imgmat.at<cv::Vec3b>(i,j)[1];
			int blu = imgmat.at<cv::Vec3b>(i,j)[0];
			fprintf(fp,"%d %d %d\n",red,gre,blu);
		}
	}
	fclose(fp);
	//=====================================================================


	//=====================================================================
	FILE *fp2 = fopen("fruits2.ppm","w");
	fprintf(fp2,"P3\n");
	fprintf(fp2,"%d %d\n",src->width,src->height);
	fprintf(fp2,"%d\n",15);
	for ( int row=0; row<src->height; ++row ) {
		for ( int col=0; col<src->width; ++col ) {
			int pos = src->nChannels*(row*src->width+col);
			uchar red = src->imageData[pos+2];//>0?src->imageData[pos+2]:255-src->imageData[pos+2];
			uchar gre = src->imageData[pos+1];//>0?src->imageData[pos+1]:255-src->imageData[pos+1];
			uchar blu = src->imageData[pos];//>0?src->imageData[pos]:255-src->imageData[pos];
			fprintf(fp2,"%d %d %d\n",red,gre,blu);

		}
	}
	fclose(fp2);

	
	//SetColorImageToSelf(src);

	IplImage *gray = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
	SetColorImageToGray(src,gray);

	IplImage *halfgray = cvCreateImage(cvSize(src->width/2,src->height/2),IPL_DEPTH_8U,1);
	CvRect halfrect = {100,100,src->width/2,src->height/2};
	CvMat matheader, *halfgraymat = cvGetMat(gray,&matheader);
	CvMat *shallowcopyhalf;
	cvGetImage(shallowcopyhalf,gray);
	cvGetSubRect(gray,halfgraymat,halfrect);

	cvNamedWindow( "showgray", CV_WINDOW_AUTOSIZE );
	cvShowImage( "showgray", gray );

	cvNamedWindow( "show", CV_WINDOW_AUTOSIZE );
	cvShowImage( "show", src );
	
	cvWaitKey(0);
}

void xtCreateImageViewer::OverSaveBMPFile()
{
	for ( int i=0; i<100000; ++i ) {
		IplImage *src = cvLoadImage("milksky.bmp");
		cvSaveImage( "milksky.bmp", src );
		cvReleaseImage(&src);
	}
}

void xtCreateImageViewer::DrawCircle()
{
	IplImage *lineimage = cvCreateImage( cvSize(1000,1000),IPL_DEPTH_8U,3 );
	cvZero(lineimage);
	CvPoint pt0 = {20,200};
	CvPoint pt1 = {500,500};
	CvScalar color = {{1.0,.5,1.0,1.0}};
	cvLine(lineimage, pt0, pt1, color, 1, 20);
	cvCircle(lineimage,pt1,40,color,10,8);
	cvNamedWindow( "show", CV_WINDOW_AUTOSIZE );
	cvShowImage( "show", lineimage );
	
	cvWaitKey(0);
	cvReleaseImage(&lineimage);
}








