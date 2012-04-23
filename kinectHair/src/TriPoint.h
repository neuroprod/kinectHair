//
//  TriPoint.h
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


#ifndef furryKinectApp_KinectPoint_h
#define furryKinectApp_KinectPoint_h

class TriPoint
{
public:
    TriPoint()
    {triIndex =-1;};
    
    ~TriPoint(){};
    
    int index;
   float screenX;
    float  screenY;
    
  
    bool inRange;
    float x;
    float y;
    float z;  
    
    int triIndex;
    float xn;
    float yn;
    float zn; 
    
    int tar;
    void normalize()
    {
        return;
        float size =sqrtf(xn*xn +yn*yn +zn*zn);
        
        xn /=size;
        yn /=size;
        zn /=size;
    
    
    }
};

#endif
