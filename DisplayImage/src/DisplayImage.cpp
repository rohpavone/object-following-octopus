
#include<stdio.h>
#include<stdlib.h>
#define OUT stdout

#include<DisplayImage.h>
using namespace std;
int sliderPosition = 0;
const char * windowName = "windowExample";

FrameDeck frames;

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
		{			fprintf( OUT, "%s ", argv[i] );
		}
		fprintf( OUT, "\n" );
	}
	return argv[1];
}


FrameDeck queryAllFrames( const char * filename )
{
	CvCapture * capture = cvCaptureFromFile( filename );
	vector<IplImage *> frames;
	FrameDeck j;
	if( capture == NULL )
	{
		fprintf( OUT, "Could not open the file\n" );
		return j;
	}
	IplImage * temp = cvQueryFrame( capture );
	while( temp != NULL)
	{
		frames.push_back( cvCloneImage( temp ) );
		temp = cvQueryFrame( capture );
	}
	j.fps = 0;
	j.fps = cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
	if( !j.fps ) j.fps = 50;
	j.frameVector = frames;
	cvReleaseCapture( &capture );

	return j;
}

int displayFramesInWindow( FrameDeck frames, const char * windowName )
{
	unsigned int i;
	for( i = 0; i < frames.frameVector.size(); i++ )
	{
		cvShowImage( windowName, frames.frameVector[i] );
		cvWaitKey( 1000 / frames.fps );
	}
	return 0;
}

/*int saveVideo( char * filename, FrameDeck frames )
{

}*/

void updateFrame( int position )
{
	cvShowImage( windowName, frames.frameVector[position] );
}
/*
int main(int argc, char * argv[])
{
	char * filename = getArguments( argc, argv );
	const char * trackbarName = "Frame number";

	if( filename == NULL ) return 1; // not proper arguments

	cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE);

	frames = queryAllFrames( filename );

	cvCreateTrackbar( trackbarName, windowName, &sliderPosition, frames.frameVector.size() - 1, (CvTrackbarCallback) updateFrame );
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
			if( sliderPosition < frames.frameVector.size() - 1 )
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition + 1 );
		}
		else if( key == 'i' ) // up
		{
			if( sliderPosition < frames.frameVector.size() - 10 )
				cvSetTrackbarPos( trackbarName, windowName, sliderPosition + 10 );
			else
				cvSetTrackbarPos( trackbarName, windowName, frames.frameVector.size() - 1 );
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
*/


