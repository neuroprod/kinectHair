/*
 *  mcPoint.cpp
 *  ofxKinect
 *
 *  Created by Kris Temmerman on 25/04/11.
 *  Copyright 2011 Neuro Productions. All rights reserved.
 *
 */

#include "mcPoint.h"
#include "ofMain.h"


mcPoint::mcPoint()
{
    numTris =0;
    nx=0;
    ny=0;
    nz=0;
}
mcPoint::~mcPoint(){}
void mcPoint::calculateNormal()
{
   
    float size =sqrtf(nx*nx+ ny*ny + nz*nz);
    
    nx /= size;
    ny /= size;
    nz /= size;

  
}
void mcPoint::addTriangle(KinectTriangle * tri)
{
    nx+= tri->xn;
    ny+= tri->yn;
    nz+= tri->zn;
    numTris++;
}
bool mcPoint::isEqual(mcPoint p)
{
    if((int)zReal !=(int) p.zReal)return false;
    if((int)xReal !=(int) p.xReal)return false;
    if ((int)yReal !=(int)p.yReal)return false;

    return true;

}

