//
//  KinnectHandler.cpp
//  ofxKinectExample
//
//  Created by Kris Temmerman on 30/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "KinectHandler.h"


double KinectHandler::fx_d = 1.0 / 5.9421434211923247e+02;
double KinectHandler::fy_d = 1.0 / 5.9104053696870778e+02;
float KinectHandler::cx_d = 3.3930780975300314e+02;
float KinectHandler::cy_d = 2.4273913761751615e+02;


int KinectHandler::width =640 ;
int KinectHandler::height=480 ;
int KinectHandler::stepSize=5;


unsigned short KinectHandler::maxDepth =1400;//680;//487;
unsigned short KinectHandler::minDepth=20;

void KinectHandler::setColorPixels(unsigned char*  pixels)
{
   colorPixels = pixels;



}

void KinectHandler::drawHair()
{
    glLineWidth(0.1);
    glEnable(GL_LINE_SMOOTH);
   
    int  s =triangles.size();
    for (int i=0;i<100000;i++){
        if (drawStep>=triangles.size())return;

        triangles[   drawStep]->drawHairs();
        drawStep++;
    }
  
}
void KinectHandler::draw()
{
    

    for (int i=0; i<triangles.size(); i++) {
        triangles[i]->draw();
    }
   /*for(int i=0;i<numPoints;i++)
    {
        if (points[i].isHit)
        ofCircle(ofPoint(  points[i].x,  points[i].y), 5);
    
    
    
    }*/
 
}

void KinectHandler::setup()
{

    
    sw =width/stepSize;
    sh  = height/stepSize;
    numPoints =sw*sh;
    
  	points =new mcPoint[numPoints]; 
    int  count =0;
    int i=0;
    int j=0;
    for(i=0;i<sh;i++)
	{
        for (j=0; j<sw;j++) 
        {
            
            //points
            points[count].y = i*stepSize ;
            points[count].x = j*stepSize ;
            
            
            count++;
            
        }
        
        
	} 
    
    cubes=new mcCube[(sw-1) *(sh-1)];
    count =0;
	for(i=0;i<sh-1;i++)
	{
        for (j=0; j<sw-1;j++) 
        {
            
            
            int pos = i*sw +j;
            cubes[count].tl = &points[pos];
            cubes[count].tr = &points[pos+1];
            
            cubes[count].bl = &points[pos+sw];
            cubes[count].br = &points[pos+1+sw];
            
            
            
            count++;
            
        }
        
        
	}

    calculateLookups() ;

}

void KinectHandler::setRawPixels(unsigned short *rawPixels)
{
 
    
    /*
     *    prep mc point
     *    
     */
    
    int val1;
    int val2;
    int pointPos;
    int x;
    int y;
    float zw;
    int i=0;
    for(i=0;i<numPoints;i++)
    {
        x = points[i].x;
        y = points[i].y;
        pointPos=y * width + x;
        val1 =rawPixels[pointPos]; 
        
        ofVec3f w =kin->getWorldCoordinateAt(x, y);
        if( w.z <maxDepth && w.z>minDepth)
        {
            //cout <<val1 <<" ";
            
            
            
            
            
            
            points[i].isHit =true;
            
            
            
            //cout << "ishit";
            points[i].zReal  =-w.z; 
            points[i].xReal = -w.x;
            points[i].yReal = -w.y;

            
            /*
            zw = distancePixelsLookup [val1];
            cout << zw <<" "<<w.z<<"\n ";
            points[i].zReal  =zw; 
            points[i].xReal = float((x - cx_d) * zw * fx_d);
            points[i].yReal = float((y - cy_d) * zw * fy_d);
         
            */
            
        }else
        {
            points[i].isHit =false;
        }
        
        
    }
  
    
    
    // cout << triangleCount1;
    
 calculateTriangles(  cubes, points,rawPixels);


}
void KinectHandler::calculateLookups() {
    
    //return;
    float
    k1 = 0.1236,
    k2 = 2842.5,
    k3 = 1.1863,
    k4 = 0.0370;
    
    for(int i = 0; i < 2048; i++){
        if(i == 2047) {
            distancePixelsLookup[i] = 0;
            
        } else {
            distancePixelsLookup[i] =(-1000 * (k1 * tanf(((i) / k2) + k3) - k4));
          //  if( distancePixelsLookup[i] >0)
			//	cout <<"lookup: "<< distancePixelsLookup[i] <<" "<< i <<"\n";
        }
        
    }
    
	
    
    
}





void KinectHandler::calculateTriangles(  mcCube *cubes, mcPoint *points, unsigned short  *pixelData)
{
    
    pointsTris.clear();
    triangles.clear();
    
    int numCubes =(sw-1)*(sh-1);
    int i;
    for(i=0;i<numCubes;i++)
    {
        
        mcCube cube =cubes[i];
        int pos=0;
        if(cube.tl->isHit )pos+=1;
        if(cube.tr->isHit )pos+=2;
        if(cube.bl->isHit )pos+=4;
        if(cube.br->isHit )pos+=8;      
        
        if(pos == 0)
        {
            continue;
        }
        
        mcPoint point1; 
        mcPoint point2 ;
        mcPoint point3 ;
        if(pos == 15)
        {
            
            
            addTriangle(cube.tl,cube.tr,cube.bl);
            addTriangle(cube.tr,cube.br,cube.bl);
        }
        
        else if(pos == 1)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.tl,cube.bl,false,pixelData);
            
            
            addTriangle(&point1,&point2,cube.tl);
            // delete &point1;
            //delete &point2;
        }
       
        else if(pos == 2)
        {
            
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            
            addTriangle(&point1,&point2,cube.tr);
            
        }
        else if(pos == 3)
        {
            
            point1 = getCrossPoint(cube.tl,cube.bl,false ,pixelData);
            point2 = getCrossPoint(cube.tr,cube.br,false,pixelData );
            
            addTriangle(cube.tl,cube.tr,&point1);
            addTriangle(cube.tr,&point2,&point1);
            
        }
        else if(pos == 4)
        {
            
            point1 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            point2= getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            addTriangle(&point1,&point2,cube.bl);
            
        }
        else if(pos == 5)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(cube.bl,&point1,&point2);
            addTriangle(cube.tl,&point1,cube.bl);
        }
        else if(pos == 8)
        {
            
            point1 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            addTriangle(&point1, cube.br,&point2);
            
        }
        else if(pos == 7)
        {
            
            
            addTriangle( cube.tl, cube.tr,cube.bl);   
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(&point1, &point2,cube.tr);
            addTriangle(&point2, cube.bl,cube.tr);        }
        else if(pos == 10)
        {
            
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            addTriangle(&point1,cube.tr ,&point2);
            addTriangle(cube.tr,cube.br,&point2);    
        }
        else if(pos == 7)
        {
            
            
            addTriangle( cube.tl, cube.tr,cube.bl); 
            point1 = getCrossPoint(cube.tr,cube.br,false,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle(&point1, &point2,cube.tr);
            addTriangle(&point2, cube.bl,cube.tr); 
            
        }   
        else    if(pos == 11)
        {
            
            addTriangle( cube.tl, cube.tr,cube.br); 
            point1 = getCrossPoint(cube.tl,cube.bl,false,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true ,pixelData);
            
            addTriangle(&point1,cube.br ,&point2);
            addTriangle(&point1, cube.tl,cube.br);
            
        }
        
        else  if(pos == 12)
        {
            
            
            point2 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            point1 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            addTriangle(&point1, &point2,cube.bl);
            addTriangle(&point2, cube.br,cube.bl); 
            
        }   
        else  if(pos == 13)
        {
            
            
            addTriangle( cube.br, cube.bl,cube.tl); 
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.tr,false,pixelData);
            addTriangle(&point1,&point2,cube.br );
            addTriangle(&point1, cube.br,cube.tl);
            
        }
        else  if(pos == 14)
        {
            
            
            addTriangle( cube.bl, cube.tr,cube.br); 
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.tl,false,pixelData);
            
            
            
            addTriangle(&point1,cube.bl ,&point2);
            addTriangle(&point1, cube.tr,cube.bl);
        }
        else  if(pos == 6)
        {
            
            point1 = getCrossPoint(cube.tr,cube.tl,true,pixelData);
            point2 = getCrossPoint(cube.bl,cube.tl,false ,pixelData);
            
            
            addTriangle( cube.tr, &point1,cube.bl); 
            addTriangle(  &point1,cube.bl,&point2); 
            
            
            
            
            point1 = getCrossPoint(cube.tr,cube.br,false ,pixelData);
            point2 = getCrossPoint(cube.bl,cube.br,true,pixelData);
            
            
            addTriangle( cube.tr, &point1,cube.bl); 
            addTriangle(  &point1,&point2,cube.bl); 
            
            
        }    else  if(pos == 9)
        {
            
            point1 = getCrossPoint(cube.tl,cube.tr,true,pixelData);
            point2 = getCrossPoint(cube.br,cube.tr,false ,pixelData);
            
            
            addTriangle( cube.tl, &point1,cube.br); 
            addTriangle(  &point1,&point2,cube.br); 
            
            
            
            
            point1 = getCrossPoint(cube.tl,cube.bl,false ,pixelData);
            point2 = getCrossPoint(cube.br,cube.bl,true,pixelData);
            
            
            addTriangle( cube.tl,cube.br, &point1); 
            addTriangle(  &point1,cube.br,&point2); 
            
            
        }
        
    }
    
    for(int i =0;i< pointsTris.size();i++)
    {
    
        pointsTris[i]->calculateNormal();
    }
    
    
}


mcPoint KinectHandler::getCrossPoint(mcPoint *onPoint,mcPoint *ofPoint,bool isHorizontal,unsigned short *depthPixelsBack)
{
    
    mcPoint crossPoint;
    int xPos;
    int yPos;
    
    int step =1;
    xPos = onPoint->x;
    yPos = onPoint->y;
    bool found = false;
    int val;
    int count=0;
    ofVec3f w;
    if(isHorizontal)
    {
        if( onPoint->x > ofPoint->x) step=-1;
        while(!found)
        {
            count++;
            if(count>stepSize)found =true;
            xPos+=step;
            
            
          w =kin->getWorldCoordinateAt(xPos, yPos);
         

            
            
            val =	 depthPixelsBack[yPos * width + xPos];	
            
            if(  w.z >maxDepth || w.z<minDepth)
            {
                xPos-=step;
                val =	 depthPixelsBack[yPos * width + xPos];
                
                found =true;
            }
            
        }
        
        
        
        
    }else
    {
        if( onPoint->y > ofPoint->y) step=-1;
        while(!found)
        {
            count++;
            if(count>stepSize)found=true;
            yPos+=step;
            
            w =kin->getWorldCoordinateAt(xPos, yPos);
            

            val =	 depthPixelsBack[yPos * width + xPos];	
            if(  w.z>maxDepth || w.z<minDepth)
            {
                
                yPos-=step;
                val =	 depthPixelsBack[yPos * width + xPos];
                
                
                
                found =true;
            }
            
            
        }
        
        
    }
    
    
    float zw = distancePixelsLookup [val];
    
    crossPoint.x =xPos;
    crossPoint.y =yPos;
      w =kin->getWorldCoordinateAt(xPos, yPos);
    
    crossPoint.zReal  =-w.z ;
    crossPoint.xReal = -w.x;//float((xPos - cx_d) * zw * fx_d);
    crossPoint.yReal = -w.y; //float((yPos - cy_d) * zw * fy_d);
     
    return crossPoint;
}
void KinectHandler::addTriangle(mcPoint *point1,mcPoint *point2,mcPoint *point3)
{
    
   
    unsigned int i;
    
    unsigned int index1;
    unsigned int index2;
    unsigned int index3;
    
    //chekPoint1;
    bool found =false;
    //cout<< point1->zReal<<" ";
    //cout<< point2->zReal<<" ";
    //cout<< point3->zReal<<" << \n";
    
    for (i=0;i<pointsTris.size();i++)
    {
        if(pointsTris[i]->isEqual(*point1))
        {
            found =true;
            index1 =(unsigned int)i;
            
            break;
        }
        
    }
   
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        pointsTris.push_back(point );
        point->index =pointsTris.size()-1;
        point->zReal =point1->zReal;
        point->xReal =point1->xReal;
        point->yReal =point1->yReal;
        point->x=point1->x;
        point->y =point1->y;
        index1 =point->index;
        
    }
    
    
    //chekPoint1;
    found =false;
    
    for (i=0;i<pointsTris.size();i++)
    {
        if(pointsTris[i]->isEqual(*point2))
        {
            found =true;
            index2 =(unsigned int)i;
            //cout <<index2<<"<-i2 ";
            break;
        }
        
    }
   
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        pointsTris.push_back(point );
        
        point->index =pointsTris.size()-1;
        point->zReal =point2->zReal;
        point->xReal =point2->xReal;
        point->yReal =point2->yReal;
        point->x=point2->x;
        point->y =point2->y;
        index2 =point->index;
        
    }
    
    
    
    //chekPoint3;
    found =false;
    
    for (i=0;i<pointsTris.size();i++)
    {
        if(pointsTris[i]->isEqual(*point3))
        {
            found =true;
            index3 =(unsigned int)i;
            // cout << " index3Set->"<< index3;
            break;
        }
        
    }
   
    
    if(!found)
    {
        mcPoint *point  =new mcPoint();
        pointsTris.push_back(point );
        point->index =pointsTris.size()-1;
        point->zReal =point3->zReal;
        point->xReal =point3->xReal;
        point->yReal =point3->yReal;
        
        point->x=point3->x;
        point->y =point3->y;
        
        index3 =point->index;
        //cout << " indexPoint->"<< index3;
        
    }
    if(index2==index1)return;
    if(index3==index1)return;
    if(index3==index2)return;
    
    KinectTriangle *tri =new KinectTriangle();
    tri->pixels =colorPixels; 
    tri->v1 =pointsTris[index1];
    tri->v2 =pointsTris[index2];
    tri->v3 =pointsTris[index3];
    triangles.push_back(tri);
    tri->calcualteNormal();
    pointsTris[index1]->addTriangle(tri );
      pointsTris[index2]->addTriangle(tri );
      pointsTris[index3]->addTriangle(tri );
  
  }
