//
//  KinectDepthTriangulation.h
//  furryKinectApp
//
//  Created by Kris Temmerman on 30/01/12.
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

#ifndef furryKinectApp_KinectDepthTriangulation_h
#define furryKinectApp_KinectDepthTriangulation_h

#define KINECT_W 640 
#define KINECT_H 480


#include <ioStream>
#include <map>
#include <vector>

#include "TriPoint.h"
#include "TriSquare.h"

#include "TriTriangle.h"
#include "ofxKinect.h"

using namespace std;
class KinectDepthTriangulation
{
      protected:
    
    
        void  addTriangle(TriPoint *point1,TriPoint *point2,TriPoint *point3);
       
    
        TriPoint * getCrossPoint(TriPoint *onPoint,TriPoint *ofPoint,bool isHorizontal);
    
        float minDepth;
        float maxDepth;
    
       
    
        TriPoint *points;
        TriSquare *squares;
    
        int numPoints;
        int numSquares;
    
       float *depthPixels;
    
        vector  < TriPoint *> pointLookup;
       
    
        int indexCount;
    
        int sh;
        int sv;
    public :
    

        KinectDepthTriangulation(){};
    
    
        void setup(int gridSubH, int gridSubW, float minDepth, float maxDepth );
        void setDepthRange(float minDepth,float maxDepth);
    
        void setRawPixels(float *rawPixels);
        void normalizeVertexNormals();
        void camToWorld(int cx, int cy,float &z, float &x, float &y);
        // output:
        vector<TriPoint > vertices;
        vector<int> indices;
        vector<TriTriangle > triangles;
};




#endif
