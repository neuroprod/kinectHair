//
//  KinnectHandler.h
//  ofxKinectExample
//
//  Created by Kris Temmerman on 30/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ofxKinectExample_KinnectHandler_h
#define ofxKinectExample_KinnectHandler_h
#include "ofMain.h"
#include "ofxKinect.h"
#import "mcPoint.h"
#import "mcCube.h"
class KinectHandler
{
 float distancePixelsLookup[2048];
    
    static int width ;
	static int height ;
    static int stepSize ;
    
    
    
    static double fx_d;	static double fy_d;
	static float cx_d;
	static float cy_d;
    
    static unsigned short maxDepth;
    static unsigned short minDepth;
    
    int numPoints;
    int sw;
    int sh;

    mcPoint *points;
    mcCube *cubes;
    
    // triangulation utils;
    void calculateTriangles(  mcCube *cubes, mcPoint *points, unsigned short *pixelData );
    void addTriangle(mcPoint *point1,mcPoint *point2,mcPoint *point3);
    mcPoint getCrossPoint(mcPoint *onPoint,mcPoint *ofPoint,bool isHorizontal,unsigned short *depthPixelsBack);

    vector<mcPoint *> pointsTris;
    vector<KinectTriangle *> triangles;  
   unsigned char*  colorPixels;
    
    
public:
    KinectHandler(){}
    
    void setup();
 void setColorPixels(unsigned char* pixels);
    void setRawPixels(unsigned short *rawPixels);
    void calculateLookups() ;
    void draw();
    void drawHair();
    int drawStep;
    ofxKinect *kin;
};

#endif
