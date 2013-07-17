// enciption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "xtCreateImageViewer.h"
#include "xtCharHelp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char **charargv = new char*[argc];
	for ( int i=0; i<argc; ++i ) {
		charargv[i] = xtCharHelp::WCharToCharPtr(argv[i]);
	}

	//xtCreateImageViewer::LoadDisplaySmoothImage();
	//xtCreateImageViewer::LoadDisplayResizeImage();
	//xtCreateImageViewer::LoadDisplaCannyProcess();
	//xtCreateImageViewer::LoadROIImage();
	//xtCreateImageViewer::LoadROIImage(argc,charargv);
	//xtCreateImageViewer::ConvertImageToGray(argc,charargv);
	xtCreateImageViewer::DumpToPPM();
	//xtCreateImageViewer::DrawCircle();

	for ( int i=0; i<argc; ++i ) {
		delete [] charargv[i];
	}
	delete []charargv;
	return 0;
}

