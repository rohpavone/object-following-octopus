#include<opencv/cvaux.h>
#include<opencv/highgui.h>
#include<opencv/cxcore.h>
#include<opencv/cv.h>


#include<stdio.h>
#include<stdlib.h>
#include <vector>
#define OUT stdout

using namespace std;
int sliderPosition = 0;
const char * windowName = "windowExample";
vector<IplImage *> frameVector;

char * getArguments(int argc, char * argv[])
{
	if( argc < 2 )
	{
		fprintf( OUT, "Not enough arguments\nDisplay.exe <filename>\n" );
		return NULL;
	}
	if( argc > 2 )
	{
		int i;
		fprintf( OUT, "Ignoring the following arguments: " );
		for( i = 2; i < argc; i++ )
		{
			fprintf( OUT, "%s ", argv[i] );
		}
		fprintf( OUT, "\n" );
	}
	return argv[1];
}


vector<IplImage *> queryAllFrames( const char * filename )
{
	CvCapture * capture = cvCaptureFromFile( filename );
	vector<IplImage *> frames;
	if( capture == NULL )
	{
		fprintf( OUT, "Could not open the file\n" );
		return frames;
	}
	IplImage * temp = cvQueryFrame( capture );
	while( temp != NULL)
	{
		frames.push_back( cvCloneImage( temp ) );
		temp = cvQueryFrame( capture );
	}
	cvReleaseCapture( &capture );
	return frames;
}

int displayFramesInWindow( vector<IplImage *> frames, const char * windowName )
{
	unsigned int i;
	for( i = 0; i < frames.size(); i++ )
	{
		cvShowImage( windowName, frames[i] );
		cvWaitKey( 20 );
	}
	return 0;
}

void updateFrame( int position )
{
	cvShowImage( windowName, frameVector[position] );
}

int main(int argc, char * argv[])
{
	char * filename = getArguments( argc, argv );
	const char * trackbarName = "Frame number";

	if( filename == NULL ) return 1; // not proper arguments

	cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE);

	frameVector = queryAllFrames( filename );

	cvCreateTrackbar( trackbarName, windowName, &sliderPosition, frameVector.size() - 1, (CvTrackbarCallback) updateFrame );
	int key;
	while( true )
	{
		key = cvWaitKey(0);
		if( key == 'j' ) // left
		{
			if( sliderPosition > 0)
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition - 1);
		}
		else if( key == 'l' ) // right
		{
			if( sliderPosition < frameVector.size() - 1 )
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition + 1 );
		}
		else if( key == 'i' ) // up
		{
			if( sliderPosition < frameVector.size() - 10 )
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition + 10 );
			else
				cvSetTrackbarPos( trackbarName, windowName, frameVector.size() - 1 );
		}
		else if( key == 'k' ) // down
		{
			if( sliderPosition > 9 )
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition - 10 );
			else
				cvSetTrackbarPos( trackbarName, windowName, 0 );
		}
		else
		{
			break;
		}
	}

	return 0;
}


