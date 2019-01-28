// FaceTracker.h : include file for FaceTracker class
// Author: Steven Jackson
//

#pragma once

#ifdef FACETRACKER_EXPORTS
#define FACETRACKER_API __declspec(dllexport) 
#else
#define FACETRACKER_API __declspec(dllimport)
#endif

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"

#include <vector>

using namespace cv;
using namespace std;


class FACETRACKER_API FaceTracker {

public:
	FaceTracker();

	bool captureCamera(int cameraId, int width, int height);
	bool getActualVideoSize(int& width, int& height);
	void releaseCamera();
	bool loadClassifierFile(const char *classifierFile);

	void update(std::vector<uchar>& buffer);

	void getFrame(cv::Mat& frame);

private:

	cv::VideoCapture* stream;
	bool m_isOpen;

	cv::CascadeClassifier* faceCascade;
};

