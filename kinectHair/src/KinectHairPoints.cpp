//
//  KinectHairPoints.cpp
//  furryKinectApp
//
//  Created by Kris Temmerman on 07/04/12.
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

#include "KinectHairPoints.h"


void KinectHairPoints::setup(int _numHairs)
{
    numHairs =_numHairs;
    weights.clear();
    // create random Barycentric weights
    for (int i=0; i<numHairs*100; i++) 
    {
        weight w;
        
        float b0 =(float)rand()/RAND_MAX;
        float b1 = (float)rand()/RAND_MAX;
        float b2 =(float)rand()/RAND_MAX;
        b0*=b0;
        b1*=b1;
        b2*=b2;

        float b  = b0 + b1 + b2;
        b0 /= b;
        b1 /= b;
        b2 /= b;   
        
        w.w1  =b0;
        w.w2  =b1;
        w.w3  =b2;
    
        weights.push_back(w);
    }
    
   


}
void KinectHairPoints::setTriangles (vector <TriTriangle  >& tri)
{
    if (useSingleColor)
    {
        setTrianglesSingleColor(tri);   
    }else
    {
         setTrianglesMultiColor(tri);   
    }

    
}






void KinectHairPoints::setHairColors(unsigned char *colors)
{
    useSingleColor =false;
    col =colors;
}

void KinectHairPoints::setHairColor(unsigned char r,unsigned char  g,unsigned char b)
{

    useSingleColor = true;
    colorR  =(float)r/255.0f;
    colorG   =(float)g/255.0f;
    colorB   =(float)b/255.0f;
}
void KinectHairPoints::setTrianglesSingleColor (vector <TriTriangle  >& tri)
{
    
      
    const int numTris = tri.size();
    float * tempData = new float [numTris*numHairs*9]; 
    numIndices  = numTris*numHairs;
    
    TriPoint *p1;
    TriPoint *p2;
    TriPoint *p3;
    
    float w1;
    float w2;
    float w3;
    
    
    
    
    int count =0;
    for (int i=0; i<numTris;i++)
    {
        
        p1 = tri[i].p1;
        p2 = tri[i].p2;
        p3 = tri[i].p3;
        int off = (float)rand()/RAND_MAX*100*numHairs;
        for (int j=0; j<numHairs; j++) 
        {
            
            w1 = weights[j+off].w1;
            w2 = weights[j+off].w2;
            w3 = weights[j+off].w3;
            
            tempData[count] = p1->x*w1 +p2->x*w2 +p3->x*w3; 
            count++;
            
            tempData[count] = p1->y*w1 +p2->y*w2 +p3->y*w3; 
            count++;
            
            tempData[count] = p1->z*w1 +p2->z*w2 +p3->z*w3; 
            count++;
            
            // put some random direction to the hairs
            // 
            if (j%3 ==0){
                
                tempData[count] = p1->xn*w1 +p2->xn*w2 +p3->xn*w3  +((float )rand()/RAND_MAX-0.5)*10;  
                count++;
                
                tempData[count] = p1->yn*w1 +p2->yn*w2 +p3->yn*w3+((float )rand()/RAND_MAX-0.5)*10; 
                count++;
                
                tempData[count] = p1->zn*w1 +p2->zn*w2 +p3->zn*w3+((float )rand()/RAND_MAX)*5;  
                count++;
                
            }else 
            {
                tempData[count] = p1->xn*w1 +p2->xn*w2 +p3->xn*w3  +((float )rand()/RAND_MAX-0.5)*2;  
                count++;
                
                tempData[count] = p1->yn*w1 +p2->yn*w2 +p3->yn*w3 +((float )rand()/RAND_MAX-0.5)*2; 
                count++;
                
                tempData[count] = p1->zn*w1 +p2->zn*w2 +p3->zn*w3;+((float )rand()/RAND_MAX-0.5)*1;  
                count++;
                
            }
            //add some variation to the single color;
            float add =powf((float )rand()/RAND_MAX,32)+0.1;
            float mult=1.0-powf((float )rand()/RAND_MAX,32)+0.1;
            tempData[count] = colorR*mult+add;  
            count++;
            
            tempData[count] =  colorG *mult +add; 
            count++;
            
            tempData[count] =  colorB* mult +add ;  
            count++;
            
            
        }
        
    }
    delete [] data;
    data = tempData;
}


void KinectHairPoints::setTrianglesMultiColor (vector <TriTriangle  >& tri)
{
    
    
    
    const int numTris = tri.size();
    float * tempData = new float [numTris*numHairs*9]; 
    numIndices  = numTris*numHairs;
    
    TriPoint *p1;
    TriPoint *p2;
    TriPoint *p3;
    
    float w1;
    float w2;
    float w3;
    
    
    
    
    int count =0;
    for (int i=0; i<numTris;i++)
    {
        
        p1 = tri[i].p1;
        p2 = tri[i].p2;
        p3 = tri[i].p3;
        int off = (float)rand()/RAND_MAX*100*numHairs;
        for (int j=0; j<numHairs; j++) 
        {
            
            w1 = weights[j+off].w1;
            w2 = weights[j+off].w2;
            w3 = weights[j+off].w3;
            
            tempData[count] = p1->x*w1 +p2->x*w2 +p3->x*w3; 
            count++;
            
            tempData[count] = p1->y*w1 +p2->y*w2 +p3->y*w3; 
            count++;
            
            tempData[count] = p1->z*w1 +p2->z*w2 +p3->z*w3; 
            count++;
            if (j%3 ==0){
                
                tempData[count] = p1->xn*w1 +p2->xn*w2 +p3->xn*w3  +((float )rand()/RAND_MAX-0.5)*10;  
                count++;
                
                tempData[count] = p1->yn*w1 +p2->yn*w2 +p3->yn*w3+((float )rand()/RAND_MAX-0.5)*10; 
                count++;
                
                tempData[count] = p1->zn*w1 +p2->zn*w2 +p3->zn*w3+((float )rand()/RAND_MAX)*5;  
                count++;
                
            }else 
            {
                tempData[count] = p1->xn*w1 +p2->xn*w2 +p3->xn*w3  +((float )rand()/RAND_MAX-0.5)*2;  
                count++;
                
                tempData[count] = p1->yn*w1 +p2->yn*w2 +p3->yn*w3 +((float )rand()/RAND_MAX-0.5)*2; 
                count++;
                
                tempData[count] = p1->zn*w1 +p2->zn*w2 +p3->zn*w3;+((float )rand()/RAND_MAX-0.5)*1;  
                count++;
                
            }
            
            // lookup the color in the position of the hair in the kinect webcam data
            int x = p1->screenX*w1  +p2->screenX*w2  +p3->screenX*w3;
            int y = p1->screenY*w1  +p2->screenY*w2  +p3->screenY*w3;
            int pos = (x+y*640)*3;
            tempData[count] = (float) col[pos]/256.0f;  
            count++;
            
            tempData[count] =  (float) col[pos+1]/256.0f;  
            count++;
            
            tempData[count] =   (float) col[pos+2]/256.0f;  
            count++;
            
            
        }
        
    }
    delete [] data;
    data = tempData;
}



