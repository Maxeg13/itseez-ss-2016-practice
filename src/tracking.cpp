#include "tracking.hpp"

#include <iostream>

using namespace std;
using namespace cv;


shared_ptr<Tracker> Tracker::CreateTracker(const string &name) {
	if (name == "median_flow") {
		return make_shared<MedianFlowTracker>();
		//return shared_ptr<Tracker>(new MedianFlowTracker);
	}
  std::cerr << "Failed to create tracker with name '" << name << "'"
            << std::endl;
  return nullptr;
}

bool MedianFlowTracker::Init(const cv::Mat &frame, const cv::Rect &roi) {
	frame_ = frame;
	position_ = roi;
	return true;
}
Rect MedianFlowTracker::Track(const cv::Mat &frame) {
	return Rect();
}
