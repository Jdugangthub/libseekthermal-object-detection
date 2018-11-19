// face detector using SEEK thermal, AUTHOR: James Dugan
//"i'm learnding!" -ralph wiggam
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/highgui/highgui.hpp>
#include "seek.h"
#include <iostream>

using namespace std;
using namespace cv;

//libseek camera activation
int main (int argc, char** argv)
{
	libseek::SeekThermalPro seek(argc == 2 ? argv[1] : "");
	cv::Mat frame, grey_frame;

	if(!seek.open()){
		std::cout << "fucked up the camera" << std::endl;
		return -1;
	}

	if(!seek.read(frame)) {
		std::cout <<"no more image" <<std::endl;
		return -1;
	}

	cv::normalize(frame, grey_frame, 0, 65535, cv::NORM_MINMAX);

	//cv::imshow("LWIR", grey_frame);

	char c = cv::waitkey(10);
	if (c == 's'){
		cv::waitkey(0);
	}
}
// opencv face detect
	//load cascades
	if(!face_cascade.load(face_cascade_name)){printf("--(!)Errzor loading\n"); return -1;};
	if(!eyes_cascade.load(eyes?cascade_name)){printf("--(!)errzor loading\n"}; return -1;};

	//read the video stream
	
	capture = cv::imshow("LWIR", grey_frame);
	if(capture){
		while(True){
			frame=cvQueryFrame(capture);
	frame = cvQueryFrame(capture);

	//apply the calssifier to the frame
		if (!frame.empty())
		{detectAndDisplay(frame);}
		else
		{printf("--(!) no captured frame -- break"); break;}

		int c waitKey(10);
		if ((char)c == 'c') {break;}

		}


	}
	return 0;
}

//function detect and display
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//detect yo face
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE,Size(30,30));

	for(size_t i=0; < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5,faces[i].height*0.5),0,0,360,Scalar(255,0,255),4,8,0);

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//detect eyes if possible
		eyes_cascade.detectMultiScale(faceROI,eyes,1.1,2,0|CV_HAAR_SCALE_IMAGE, Size(30,30));

		for(size_t j = 0; j<eyes.size(); j++)
			{
				Point center(faces[i].x+eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
				int radius = cvRound((eyes[j].width+eyes[j].height)*0.25);
				circle(frame, center, radius, Scalar(255,0,0),4,8,0);
			}
		}
		//show me what you got!
		imshow(widnow_name,frame);
}
