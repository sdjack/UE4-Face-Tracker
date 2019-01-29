#pragma once

#include <opencv2/core.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace FaceTracking
{
	class FaceTracker
	{
	public:
		static bool captureCamera(int cameraId, int width, int height);

		static bool getActualVideoSize(int& width, int& height);

		static bool loadClassifierFile(const char *classifierFile);

		static void trackingUpdate(std::vector<uchar>& buffer);

		static void releaseCamera();

		static void getFrame(cv::Mat& frame);
	};
}