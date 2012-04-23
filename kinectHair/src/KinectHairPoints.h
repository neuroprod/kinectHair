//
//  KinectHairPoints.h
//  furryKinectApp
//
//  Created by Kris Temmerman on 07/04/12.
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

#ifndef furryKinectApp_KinectHairPoints_h
#define furryKinectApp_KinectHairPoints_h

#include <ioStream>
#include <vector>
#include "TriPoint.h"
#include "TriTriangle.h"


using namespace std;

struct weight
{
    float w1;
    float w2;
    float w3;

};

class KinectHairPoints{

private:
    float colorR ;
    float colorG ;
    float colorB ;
    bool useSingleColor ;
    unsigned char *col;
    
    void setTrianglesSingleColor ( vector<TriTriangle > &tri );
    void setTrianglesMultiColor ( vector<TriTriangle > &tri );
    
public:
    KinectHairPoints (){
        data =0; 
        useSingleColor = true;
        colorR  =0.2;
        colorG   =0.2;
        colorB   =0.2;
    };
    void setup(int numHairs);
    void setTriangles ( vector<TriTriangle > &tri );

    void setHairColors(unsigned char *colors);

    void setHairColor(unsigned char r,unsigned char  g,unsigned char b);
    
    
    vector<weight> weights;
    float *data;
    int numHairs;
    
    int numIndices;
    
};


#endif
