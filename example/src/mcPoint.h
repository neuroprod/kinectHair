/*
 *  mcPoint.h
 *  ofxKinect
 *
 *  Created by Kris Temmerman on 25/04/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#pragma once

#include <vector>
#import "KinectTriangle.h"

using namespace std;
class KinectTriangle;
class mcPoint {
public:
    
  
	mcPoint();
    ~mcPoint();
    void addTriangle(KinectTriangle *);
    void calculateNormal();
    
    bool isEqual(mcPoint);
    int numTris;
    unsigned int index;
    
    
    
	float x;
	float y;
	bool isHit;
	
	float xReal;
    float yReal;
    float zReal;
    
    float  nx;
    float ny;
    float nz;
};