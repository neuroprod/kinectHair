//
//  KinectTriangle.h
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#pragma once


#import "mcPoint.h"
#import "ofMain.h"
#import "ofxKinect.h"
class mcPoint;
class KinectTriangle
{
public:
 
    
    unsigned char *pixels;
    
    mcPoint *v1;
    mcPoint *v2;
    mcPoint *v3;
    float uvx;
    float uvy;
    
    ofVec3f v0vec;
    ofVec3f v1vec;
    ofVec3f v2vec;
    
    ofVec3f lightDir;
    
    
    void calcualteNormal();
    float xn;
    float yn;
    float zn;
    void draw();
    void drawHairs ();
 void drawHair( ofVec3f begin, ofVec3f normal ,ofVec3f color  );
   void drawHairColor( ofVec3f begin, ofVec3f normal ,ofVec3f color  ); 
    void getBar(ofVec3f intersectionPoint);
    float barMass( ofVec3f p, ofVec3f l0,ofVec3f l1) ;
    
};
    
