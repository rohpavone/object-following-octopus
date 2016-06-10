/*
 * test_displayImage.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: Bones
 */
#include <DisplayImage.h>
#include <gtest/gtest.h>
#include <ctime>
#define MIN_FRAME 0
#define MAX_FRAME 163
#define numberOfTests 5



using namespace std;
const char * testFile = "http://techslides.com/demos/sample-videos/small.ogv";
int sameImage( IplImage * , IplImage *  );

TEST(GetFramesTest, positive){
	FrameDeck framesTest = queryAllFrames( testFile );
	CvCapture * testCapture = cvCaptureFromFile( testFile );
	IplImage * testFramesIpl[numberOfTests];
	int testFrames[numberOfTests];
	int i;

	cout << "Frames under test: " << endl;
	for( i = 0; i < numberOfTests; i++ )
	{
		testFrames[i] = rand() % MAX_FRAME;
		cout << testFrames[i] << endl;
	}
	for( i = 0; i < numberOfTests; i++ )
	{
		cvSetCaptureProperty( testCapture, CV_CAP_PROP_POS_FRAMES, testFrames[i]);
		testFramesIpl[i] = cvQueryFrame( testCapture );
		ASSERT_TRUE( !sameImage( framesTest.frameVector[testFrames[i]], testFramesIpl[i]) );
	}
}

int sameImage( IplImage * first, IplImage * second )
{
	int i, lengthOfArray1, lengthOfArray2;
	lengthOfArray1 = first->nChannels * first->width * first->height;
	lengthOfArray2 = second->nChannels * second->width * second->height;
	if( lengthOfArray1 != lengthOfArray2 ) return 1;

	for( i = 0; i < lengthOfArray1; i++ )
	{
		if( first->imageData[i] != second->imageData[i] ) return 1;
	}

	return 0; // essentially the same frame
}



