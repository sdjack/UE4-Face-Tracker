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
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void getFrame(cv::Mat& frame);

extern "C" FACETRACKER_API bool captureCamera(int cameraId, int width, int height);
extern "C" FACETRACKER_API bool getActualVideoSize(int& width, int& height);
extern "C" FACETRACKER_API void releaseCamera();
extern "C" FACETRACKER_API bool loadClassifierFile(const char *classifierFile);
extern "C" FACETRACKER_API void trackingUpdate(std::vector<uchar>& buffer);

