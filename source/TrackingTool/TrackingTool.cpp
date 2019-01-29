// TrackingTool.cpp : Defines the exported functions for the DLL application.
// Author: Steven Jackson
//

#include "header.h"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

TrackingTool::TrackingTool()
{
	m_isOpen = false;
}

bool TrackingTool::captureCamera(int cameraId, int width, int height)
{
	stream = new cv::VideoCapture();
	stream->open(cameraId);
	stream->set(CV_CAP_PROP_FRAME_WIDTH, width);
	stream->set(CV_CAP_PROP_FRAME_HEIGHT, height);

	m_isOpen = stream->isOpened();
	return m_isOpen;
}

bool TrackingTool::getActualVideoSize(int& width, int& height)
{
	if (m_isOpen && stream != nullptr) {
		cv::Mat frame;
		getFrame(frame);

		if (!frame.data) {
			return false;
		}

		width = frame.size().width;
		height = frame.size().height;
		return true;
	}
	return false;
}

void TrackingTool::releaseCamera()
{
	if (m_isOpen && stream != nullptr && stream->isOpened()) {
		stream->release();
		delete stream;
	}

	m_isOpen = false;
}

bool TrackingTool::loadClassifierFile(const char *classifierFile)
{
	return faceCascade.load(classifierFile);
}

void TrackingTool::getFrame(cv::Mat& frame)
{
	if (!m_isOpen) {
		return;
	}

	stream->read(frame);

}

void TrackingTool::update(std::vector<uchar>& buffer)
{
	cv::Mat frame;
	getFrame(frame);

	if (!frame.data) {
		return;
	}

	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
	cv::equalizeHist(frame_gray, frame_gray);

	faceCascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(
			faces[i].x + faces[i].width*0.5,
			faces[i].y + faces[i].height*0.5
		);
		cv::ellipse(
			frame,
			center,
			cv::Size(
				faces[i].width*0.5,
				faces[i].height*0.5),
			0,
			0,
			360,
			cv::Scalar(255, 0, 255),
			4,
			8,
			0
		);
	}

	(buffer).assign(frame.datastart, frame.dataend);
}

