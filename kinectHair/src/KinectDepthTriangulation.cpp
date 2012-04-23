//
//  KinectDepthTriangulation.cpp
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

#include "KinectDepthTriangulation.h"

#include <iostream>
using namespace std; 


void KinectDepthTriangulation::setup(int gridSubH,int gridSubV, float minDepth, float maxDepth)
{
    // create testquares and there test point;
 
    setDepthRange(minDepth, maxDepth);
   
    
    sh =KINECT_W/gridSubH;  
    sv =KINECT_H/gridSubV;
  
    numPoints =gridSubH*gridSubV;
  
  	points =new TriPoint[numPoints]; 
    int  count =0;
    int x=0;
    int y=0;
    for(y=0;y<gridSubV;y++)
	{
        for (x=0; x<gridSubH;x++) 
        {
            points[count].index = x * sh + y*sv * KINECT_W ;
           
            points[count].screenX = x * sh;
            points[count].screenY = y * sv;
           
            count++;
            
        }
      
        
	} 
    numSquares  = (gridSubH-1) *(gridSubV-1);
    squares=new TriSquare[numSquares ];
    count =0;
    int pos;
    TriSquare *s ;
	for(y=0;y<gridSubV-1;y++)
	{
        for (x=0; x<gridSubH-1;x++) 
        {
            
            pos = y*gridSubH +x;
            s =  &squares[count];
            s->tl = &points[pos];
            s->tr = &points[pos+1];
            
            s->bl = &points[pos+gridSubH];
            s->br = &points[pos+1+gridSubH];
            
            count++;
            
        }
        
	}
}

void KinectDepthTriangulation::setDepthRange(float _minDepth, float _maxDepth)
{
    
 
    minDepth =_minDepth;
    maxDepth =_maxDepth;
    
    cout << "minDepth:"<<   minDepth<< " maxDepth:"<<   minDepth << endl;
    

}

void KinectDepthTriangulation::setRawPixels(float *rawPixels)
{
    
    //clean up the previous data;
    pointLookup.clear();
    vertices.clear();
    indices.clear();
    triangles.clear();
    indexCount =0;
    
    ///see of the grid points fall in the depth range;
    
    depthPixels =rawPixels;
    float zw;
    int i=0;
  
    int zPos;
    TriPoint *point;
    for(i=0;i<numPoints;i++)
    {
        point  = &points[i];
        zPos =rawPixels[point->index]; 
        
          
        if( zPos <maxDepth && zPos>minDepth)
        {
            point->inRange =true;
            point->triIndex =-1;
            point->xn =0;
            point->yn =0;
            point->zn =0;
            
            point->z =zPos;
            
            camToWorld( point->screenX,point->screenY,point->z, point->x , point->y);
            
        
        }else
        {
            point->inRange =false;
        
        }
    }
    
 
    //triangulate the squares, marching squares (much like marching cubes, but in 2D)
    //more info: http://en.wikipedia.org/wiki/Marching_squares
  
 
  
    for(i=0;i<numSquares;i++)
    {
        
          TriSquare *square=&squares[i];
        int pos=0;
        if(square->tl->inRange )pos+=1;
        if(square->tr->inRange )pos+=2;
        if(square->bl->inRange )pos+=4;
        if(square->br->inRange )pos+=8;      
        
        if(pos == 0)
        {
            continue;
            // now points of the square are in the depth range. we can continue
        }
      
        TriPoint *point1; 
        TriPoint *point2 ;
        TriPoint *point3 ;
         TriPoint *point4 ;
        if(pos == 15)
        {
            
            
            addTriangle(square->tl,square->tr,square->bl);
            addTriangle(square->tr,square->br,square->bl);
            // all points in the depth range
        }
        else if(pos == 1)
        {
            
            point1 = getCrossPoint(square->tl,square->tr,true);
            point2 = getCrossPoint(square->tl,square->bl,false);
            
            
           addTriangle(point1,point2,square->tl);
            
        }
        
        else if(pos == 2)
        {
            
            point1 = getCrossPoint(square->tr,square->br,false);
            point2 = getCrossPoint(square->tr,square->tl,true);
            
           addTriangle(point1,point2,square->tr);
            
        }
        else if(pos == 3)
        {
            
            point1 = getCrossPoint(square->tl,square->bl,false );
            point2 = getCrossPoint(square->tr,square->br,false);
            
            addTriangle(square->tl,square->tr,point1);
            addTriangle(square->tr,point2,point1);
            
        }
        else if(pos == 4)
        {
            
            point1 = getCrossPoint(square->bl,square->tl,false);
            point2= getCrossPoint(square->bl,square->br,true);
            
           addTriangle(point1,point2,square->bl);
            
        }
        else if(pos == 5)
        {
            
            point1 = getCrossPoint(square->tl,square->tr,true);
            point2 = getCrossPoint(square->bl,square->br,true);
            
            
            addTriangle(square->bl,point1,point2);
            addTriangle(square->tl,point1,square->bl);
        }
        else if(pos == 8)
        {
            
            point1 = getCrossPoint(square->br,square->tr,false);
            point2 = getCrossPoint(square->br,square->bl,true);
           
            addTriangle(point1, square->br,point2);
            
        }
        else if(pos == 7)
        {
            
            
            addTriangle( square->tl, square->tr,square->bl);   
            point1 = getCrossPoint(square->tr,square->br,false);
            point2 = getCrossPoint(square->bl,square->br,true);
            
            
            addTriangle(point1, point2,square->tr);
            addTriangle(point2, square->bl,square->tr);     
        }
        else if(pos == 10)
        {
            
            point1 = getCrossPoint(square->tr,square->tl,true);
            point2 = getCrossPoint(square->br,square->bl,true);
            //?
           addTriangle(point1,square->tr ,point2);
            
            
            addTriangle(square->tr,square->br,point2);    
        }
        else if(pos == 7)
        {
            
            
            addTriangle( square->tl, square->tr,square->bl); 
            point1 = getCrossPoint(square->tr,square->br,false);
            point2 = getCrossPoint(square->bl,square->br,true);
                     
            addTriangle(point1, point2,square->tr);
            addTriangle(point2, square->bl,square->tr); 
            
        }   
        else    if(pos == 11)
        {
            
            addTriangle( square->tl, square->tr,square->br); 
            point1 = getCrossPoint(square->tl,square->bl,false);
            point2 = getCrossPoint(square->br,square->bl,true );
            
            addTriangle(point1,square->br ,point2);
            addTriangle(point1, square->tl,square->br);
            
        }
        
        else  if(pos == 12)
        {
            
            
            point2 = getCrossPoint(square->br,square->tr,false);
            point1 = getCrossPoint(square->bl,square->tl,false);
            
            addTriangle(point1, point2,square->bl);
            addTriangle(point2, square->br,square->bl); 
            
        }   
        else  if(pos == 13)
        {
            
            
            addTriangle( square->br, square->bl,square->tl); 
            point1 = getCrossPoint(square->tl,square->tr,true);
            point2 = getCrossPoint(square->br,square->tr,false);
            addTriangle(point1,point2,square->br );
            addTriangle(point1, square->br,square->tl);
            
        }
        else  if(pos == 14)
        {
            
            
            addTriangle( square->bl, square->tr,square->br); 
            point1 = getCrossPoint(square->tr,square->tl,true);
            point2 = getCrossPoint(square->bl,square->tl,false);
            
            
            
            addTriangle(point1,square->bl ,point2);
            addTriangle(point1, square->tr,square->bl);
        }
        else  if(pos == 6)
        {
            
            point1 = getCrossPoint(square->tr,square->tl,true);
            point2 = getCrossPoint(square->bl,square->tl,false );
            
            
            addTriangle( square->tr, point1,square->bl); 
            addTriangle(  point1,square->bl,point2); 
            
            
            
            
            point3 = getCrossPoint(square->tr,square->br,false );
            point4 = getCrossPoint(square->bl,square->br,true);
            
            
            addTriangle( square->tr, point3,square->bl); 
            addTriangle(  point3,point4,square->bl); 
            
            
        }    else  if(pos == 9)
        {
         
            point1 = getCrossPoint(square->tl,square->tr,true);
            point2 = getCrossPoint(square->br,square->tr,false );
            
            
            addTriangle( square->tl, point1,square->br); 
            addTriangle(  point1,point2,square->br); 
         
            
            
            
            point3 = getCrossPoint(square->tl,square->bl,false );
            point4 = getCrossPoint(square->br,square->bl,true);
            
         
          addTriangle( square->tl,square->br, point3); 
          addTriangle(  point3,square->br,point4); 
            
            
        }
        
    }
    

}

// searches the edge of a square to find the last point that fals in the deprh range 

TriPoint * KinectDepthTriangulation::getCrossPoint(TriPoint *onPoint,TriPoint *ofPoint,bool isHorizontal)
{
    
    
   
    
    int step =1;
    
    int xPos = onPoint->screenX;
    int yPos = onPoint->screenY;
    
    bool found = false;
    float zPos;
    int count=-1;
  
    if(isHorizontal)
    {
        if( onPoint->screenX > ofPoint->screenX) step=-1;
        while(!found)
        {
            count++;
            if (count==sh-1)found =true ;
           
          
            xPos+=step;
            
            zPos  =depthPixels[yPos * KINECT_W+ xPos];
          
            if(  zPos >maxDepth || zPos<minDepth)
            {
                xPos-=step;
                            
                found =true;
            }
            
        }
        
        
        
        
    }else
    {
        if( onPoint->screenY >ofPoint->screenY ) step=-1;
        while(!found)
        {
            count++;
            if (count==sv-1)found =true ;
            yPos+=step;
         
            zPos =depthPixels[yPos * KINECT_W+ xPos];	
            
            if(  zPos >maxDepth || zPos <minDepth)
            {
                
                yPos-=step;
                
                found =true;
            }
            
            
        }
        
        
    }
    
    int tar = yPos * KINECT_W+ xPos;
    zPos =depthPixels[tar];
    
    
    for (int i =0; i< pointLookup.size();i++)
    {
        if (pointLookup[i ]->tar == tar )
        {
           
           return pointLookup[i ];
        
        
        }
    
    
    }
    
    
    
    TriPoint *point  =new TriPoint();
    point->tar  =tar;
    point->screenX =xPos;
    point->screenY =yPos;
    point->triIndex =-1;
    point->xn=0;
    point->yn=0;
    point->zn=0;
    point->inRange =false;
    point->z =  zPos;
    camToWorld( point->screenX,point->screenY,point->z, point->x , point->y);
   
    pointLookup.push_back(point);
    return point;
  
    
}

void KinectDepthTriangulation::addTriangle(TriPoint *point1,TriPoint *point2,TriPoint *point3)
{

    
    //Calculate the normal of the triangle
    
    float  x1 =point1->x -point2->x;
    float  y1 =point1->y -point2->y;
    float  z1 =point1->z -point2->z;
    
    
	float  x2 =point3->x-point2->x;
    float  y2 =point3->y -point2->y;
    float  z2 =point3->z -point2->z;
    
    float xc =y1*z2 -y2*z1;
    float yc =x1*z2 -x2*z1;
    float zc =x1*y2-x2*y1;
    
    float size =sqrtf(xc*xc +yc*yc +zc*zc);
    if (size ==0) return;
    float xn =-xc/size;
    float yn =-yc/size;
    float zn =-zc/size;
    
  
    // add the normal to the point normal
    // the poiny normals should be normalized in the end , but most of the time, it's best done in the shader
    // call normalizeVertexNormals() if you want to do that straitaway
    point3->xn +=xn ;
    point2->xn +=xn;
    point1->xn +=xn;
    
    point3->yn +=yn ;
    point2->yn +=yn;
    point1->yn +=yn;
    
    point3->zn +=zn ;
    point2->zn +=zn;
    point1->zn +=zn;
    
    // give an unique index to the point, 
    // + store a copy of all the used points in one vector
    if (point1->triIndex ==-1)
    {
        point1->triIndex =indexCount;
        vertices.push_back(*point1);
        indexCount++;
    
    }else 
    {
        vertices[point1->triIndex].xn = point1->xn;
        vertices[point1->triIndex].yn = point1->yn;
        vertices[point1->triIndex].zn = point1->zn;
    }
     
    if (point2->triIndex ==-1)
    {
        point2->triIndex =indexCount;
        vertices.push_back(*point2);
        indexCount++;
        
    }else 
    {
        vertices[point2->triIndex].xn = point2->xn;
        vertices[point2->triIndex].yn = point2->yn;
        vertices[point2->triIndex].zn = point2->zn;
    }

     
    if (point3->triIndex ==-1)
    {
        point3->triIndex =indexCount;
          vertices.push_back(*point3);
        indexCount++;
        
    }else 
    {
        vertices[point3->triIndex].xn = point3->xn;
        vertices[point3->triIndex].yn = point3->yn;
        vertices[point3->triIndex].zn = point3->zn;
    }

  
    indices.push_back(point1->triIndex );
    indices.push_back(point2->triIndex );
    indices.push_back(point3->triIndex );
    
    TriTriangle t;
    t.p1 =  &vertices[point1->triIndex];
    t.p2 =  &vertices[point2->triIndex];
    t.p3 =  &vertices[point3->triIndex];
    triangles.push_back(t );
}

// normalizes the normals off the output vertices
void KinectDepthTriangulation::normalizeVertexNormals(){

    for (int i=0;i< vertices.size();i++)
    {
      vertices[i].normalize();
    }

}
//
// calculatest the real world coordiantes
void KinectDepthTriangulation::camToWorld(int cx, int cy,float &z, float &x, float &y)
{
   // not sure if this is correct for new kinects?
    double factor = -2.0 * 0.1042 * (float)z / 120.0 ;
	x = (double)(cx - KINECT_W/2) * factor;
	y = (double)(cy - KINECT_H/2) * factor;

}


