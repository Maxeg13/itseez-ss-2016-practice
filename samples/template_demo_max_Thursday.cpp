#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

//#include "workaround.hpp"
//#include "opencv2/nonfree/features2d.hpp"
#include "detection.hpp"
#include "tracking.hpp"

using namespace std;
using namespace cv;

const char* kAbout = "Application for practice #1.";
Mat dest;
const char* kOptions =
"{ @image         |        | image to process         }"
"{ t              |  128   | threshold                }"
"{ h ? help usage |        | print help message       }";

int main(int argc, const char** argv) {
	VideoCapture cap("../../test/test_data/video/logo.mp4");
	CascadeDetector CD;
	std::vector<Rect> faces;
	std::vector<double> scores;
	Mat frame[2];

	vector<Point2f>  ptr;
	vector<Point2f>  ptrPr;
	Rect tracks(10, 10, 400, 400);
	vector<uchar> status;
	vector<float> err;

	CD.Init("../../test/test_data/detection/cascades/opencv_logo_cascade.xml");

	


	std::shared_ptr<Tracker> medFlRr = Tracker::CreateTracker("median_flow");
	int minHessian = 400;
	
	cap >> frame[0];
		medFlRr->Init(frame[0], tracks);

	const string kDstWindowName = "Destination image";
	for (;;)
	{
		frame[0].copyTo(frame[1]);
		cap >> frame[0];

		// Find key points in frame[0](tracks). 
		cv::goodFeaturesToTrack();
		
		cv::calcOpticalFlowPyrLK(
			frame[0],
			frame[1],
			ptrPr, 
			ptr, 
			status, 
			err);

		tracks = medFlRr->Track(frame[0]);
		cv::rectangle(frame[0], tracks, CV_RGB(0, 255, 0));
		
		CD.Detect(frame[0], faces, scores);
			for (int i = 0; i < faces.size(); i++)
			cv::rectangle(frame[0], faces[i], CV_RGB(255, 0, 0));

			

					//}
	//catch (const std::exception& ex) {
	//	cout << ex.what() << endl;
	//	return 0;
	//}

	// Show destination image.		
		//kDstWindowName;
		namedWindow(kDstWindowName, WINDOW_NORMAL);
		resizeWindow(kDstWindowName, 640, 480);
		imshow(kDstWindowName, frame[0]);
		waitKey(5);
	}
	return 0;
}




//std::shared_ptr<Detector> CreateDetector("cascade");


//const int threshold = parser.get<int>("t");
//try {
//cvtColor(src, src, CV_RGB2GRAY);
//cvtColor(src, src, CV_GRAY2RGB);
//processor.CvtColor(src, roi);
//processor.Filter(src, roi, 20); 
//processor.DetectEdges(src, roi,	3,  10, 2,3 );



// Parse command line arguments.

//CommandLineParser parser(argc, argv, kOptions);
//parser.about(kAbout);

// If help option is given, print help message and exit.
//if (parser.has("help")) {
//	parser.printMessage();
//	return 0;
//}

// Read image.
//Mat frame = imread(parser.get<string>(0), CV_LOAD_IMAGE_COLOR);

//if (frame.empty()) {
//	cout << "Failed to open image file '" + parser.get<string>(0) + "'."
//		<< endl;
//	return 0;
//}

// Show source image.
//const string kSrcWindowName = "Source image";
//const int kWaitKeyDelay = 1;
//namedWindow(kSrcWindowName, WINDOW_NORMAL);
//resizeWindow(kSrcWindowName, 640, 480);
//imshow(kSrcWindowName, src);
//waitKey(kWaitKeyDelay);


// Threshold data.