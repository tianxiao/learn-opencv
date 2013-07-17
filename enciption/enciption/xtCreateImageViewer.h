#pragma once

// see the Forward declaration of a typedef in C++
// http://stackoverflow.com/questions/804894/forward-declaration-of-a-typedef-in-c
struct _IplImage;
typedef _IplImage IplImage;
class xtCreateImageViewer
{
public:
	xtCreateImageViewer(void);
	~xtCreateImageViewer(void);


	static void LoadDisplayImage();

	static void LoadDisplaySmoothImage();

	static void LoadDisplayResizeImage();

	static void LoadDisplaCannyProcess();
	static IplImage* DoCanny(IplImage *in, double lowThresh, double highThresh, double aperture);

	static void LoadROIImage();

	static void LoadROIImage(int arv, char *argv[]);

	static void ConvertImageToGray(int arv, char *argv[]);

	static void DumpToPPM();

	static void OverSaveBMPFile();

	static void DrawCircle();
};

