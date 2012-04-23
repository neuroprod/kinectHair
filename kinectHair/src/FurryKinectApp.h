//
//  FurryKinectApp.h
//  furryKinectApp
//
//  Created by Kris Temmerman on 06/04/12.
// 
//  Copyright (C) 2012 Kris Temmerman,  www.neuroproductions.be
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
//  is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef furryKinectApp_FurryKinectApp_h
#define furryKinectApp_FurryKinectApp_h


#include "ofBaseApp.h"
#include "ofxKinect.h"
#include "KinectDepthTriangulation.h"
#include "KinectHairPoints.h"
#include "Camera.h"
#include "TriangleRenderer.h"
#include "HairRenderer.h"

class FurryKinectApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
    
	
	void keyPressed (int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	ofxKinect kinect;
	KinectDepthTriangulation triangulate;
    KinectHairPoints hairPoints;
    
    Camera *cam;
    TriangleRenderer triRenderer;
    HairRenderer hairRenderer;
    
    bool isDirty;
    
    int minDistance;
    int maxDistance;
    
    void prepTriData();
    float *vertices;
    uint *indices;
    int numIndices;
    int numVertices;
    
    
    float angle;
    bool  useRealColors;
    
};



#endif
