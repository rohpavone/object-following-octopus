/*
 * DisplayImage.h
 *
 *  Created on: Jun 9, 2016
 *      Author: Bones
 */

#ifndef DISPLAYIMAGE_H_
#define DISPLAYIMAGE_H_
#include<vector>
#include<opencv/cxcore.h>
#include<opencv/cv.h>
#include<opencv/highgui.h>
typedef struct FrameDeck
{
	std::vector<IplImage *> frameVector;
	double fps;
} FrameDeck;
FrameDeck queryAllFrames( const char * filename );
#endif /* DISPLAYIMAGE_H_ */
