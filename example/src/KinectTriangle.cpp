//
//  KinectTriangle.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 03/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "KinectTriangle.h"

#include "ofMain.h"

using namespace std;

void KinectTriangle::calcualteNormal()
{
    
    float  x1 =v1->xReal -v2->xReal;
    float  y1 =v1->yReal -v2->yReal;
    float  z1 =v1->zReal -v2->zReal;
    
    			
	float  x2 =v3->xReal -v2->xReal;
    float  y2 =v3->yReal -v2->yReal;
    float  z2 =v3->zReal -v2->zReal;
    
    float xc =y1*z2 -y2*z1;
    float yc = x1*z2 -x2*z1;
    float zc =x1*y2-x2*y1;
 
    float size =sqrtf(xc*xc +yc*yc +zc*zc);
    
    xn =-xc/size;
    yn =yc/size;
    zn =-zc/size;
    
    lightDir.set(20,20,100);
    lightDir.normalize();
    
}
void  KinectTriangle::draw ()
{
    glBegin(GL_TRIANGLES);

        glColor3f((v1->nx+1.0)/2.0,(v1->ny+1.0)/2.0,(v1->nz+1.0)/2.0);
        glVertex3f( v1->xReal,v1->yReal,v1->zReal);
    glColor3f((v2->nx+1.0)/2.0,(v2->ny+1.0)/2.0,(v2->nz+1.0)/2.0);
   glVertex3f( v2->xReal,v2->yReal,v2->zReal);
    
    glColor3f((v3->nx+1.0)/2.0,(v3->ny+1.0)/2.0,(v3->nz+1.0)/2.0);
    glVertex3f( v3->xReal,v3->yReal,v3->zReal);
          glEnd(); 
    

    glBegin(GL_LINE_LOOP);
    
    glColor3f(0,0,0);
    glVertex3f( v1->xReal,v1->yReal,v1->zReal);

    glVertex3f( v2->xReal,v2->yReal,v2->zReal);
    

    glVertex3f( v3->xReal,v3->yReal,v3->zReal);
    glEnd();
    
      
    
    
  



}
void  KinectTriangle::drawHairs ()
{

    
    
   
    
    
   float pointSteps =40.0;
    vector <ofVec3f> line1Vec;
    vector <ofVec3f> line2Vec;
       

    
    float step = 1.0/(float)pointSteps;
    float factor2;
    float factor1;
    float  pointX ;
    float pointY;
    float pointZ;
    
    v0vec.set(v1->xReal,v1->yReal,v1->zReal);
    v1vec.set(v2->xReal,v2->yReal,v2->zReal);
    
    v2vec.set(v3->xReal,v3->yReal,v3->zReal);
    
    
    for (int i =0;i<=pointSteps;i++)
    {
        factor1 = 1.0-((float)i*step);
        factor2 =((float)i*step);
        
        
        pointX = ((v1->xReal*factor1)+(v2->xReal*factor2));
        pointY = ((v1->yReal*factor1)+(v2->yReal *factor2));
        pointZ =  ((v1->zReal*factor1)+(v2->zReal*factor2))   ;      
        line1Vec.push_back(ofVec3f(pointX,pointY,pointZ));
      
        //var hair:Hair =new Hair(pointX,pointY,pointZ,n)
        
        pointX = ((v1->xReal*factor1)+(v3->xReal*factor2));
        pointY = ((v1->yReal*factor1)+(v3->yReal*factor2));
        pointZ=  ((v1->zReal*factor1)+(v3->zReal*factor2));   
        line2Vec.push_back(ofVec3f(pointX,pointY,pointZ));
        //lineVec.push(pointX,pointY,pointZ)
        
    }
    int count =0;
   glBegin(GL_LINES);
    for (int i =0;i<line1Vec.size();i++)
    {
        count++;
        
        for (int j =1;j<count;j++)
        {
            step  = 1.0/(float)count;
            factor1 = 1.0-((float)j*step);
            factor2 =((float)j*step);
            
            pointX =-((line1Vec[i].x*factor1)+(line2Vec[i].x*factor2));
            pointY = ((line1Vec[i].y*factor1)+(line2Vec[i].y*factor2));
            pointZ=  ((line1Vec[i].z*factor1)+(line2Vec[i].z*factor2))          ;
            
                       
            float r = (float)rand()/RAND_MAX/2.0;
            ofVec3f intpoint;
            intpoint.set(pointX ,   pointY,  pointZ);
            getBar( intpoint);
           
            int pos =       ((int)uvx +(int)uvy *640 )  *3; 
            ofVec3f color;  
            
            color.set ((float) pixels[pos]/255.0 ,(float) pixels[pos+1]/255.0 ,(float) pixels[pos+2]/255.0) ;
            
          //  color.set(0.4,0.4,0.4);
            
            color.x += (float)rand()/(RAND_MAX)/40.0;
            color.x *=1.0- (float)rand()/(RAND_MAX)/20.0;
            
            color.y += (float)rand()/(RAND_MAX)/40.0;
            color.y *=1.0- (float)rand()/(RAND_MAX)/20.0;
            color.z += (float)rand()/(RAND_MAX)/40.0;
            color.z *= 1.0-(float)rand()/(RAND_MAX)/20.0;
            
            
            
            if((float)rand()/(RAND_MAX)>0.9){
                r= (float)rand()/(RAND_MAX);
            if (r<0.5) r+=0.5;
            color *= (1.0-(r*r*r*r*r));
            }
           
           drawHair( intpoint , ofVec3f(-xn, yn, zn) ,  color);
           // drawHairColor( intpoint , ofVec3f(-xn, yn, zn) ,  color);
        }
    }
    glEnd();         
    
}
void KinectTriangle::getBar(ofVec3f intersectionPoint)
{
    float b0  = barMass(intersectionPoint, v1vec, v2vec);
    float b1  = barMass(intersectionPoint, v0vec, v2vec);
    float  b2  = barMass(intersectionPoint, v0vec, v1vec);
    
   float b  = b0 + b1 + b2;
    b0 /= b;
    b1 /= b;
    b2 /= b;
 
 
    uvx = v1->x * b0 + v2->x * b1 + v3->x * b2;
    uvy = v1->y * b0 +v2->y * b1 + v3->y * b2 ;
   
    xn = v1->nx * b0 + v2->nx * b1 + v3->nx * b2;
     yn = v1->ny * b0 + v2->ny * b1 + v3->ny * b2;
      zn = v1->nz * b0 + v2->nz * b1 + v3->nz * b2;
}

float KinectTriangle::barMass( ofVec3f p, ofVec3f l0,ofVec3f l1) 
{
    ofVec3f v = l0-l1;
    ofVec3f w = p-l0;
    
    float  c1  = v.dot(w);
    float  c2  = v.dot(v);
    float  b  = c1 / c2;
    v*= b;
    ofVec3f pB  = l0+v;
    ofVec3f  t1 = pB-p ;
    ofVec3f t2  = l0-l1 ;
    return t1.length() * t2.length();
}
void KinectTriangle::drawHairColor( ofVec3f begin, ofVec3f normal ,ofVec3f color  )
{
    
    normal.x+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.y+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.z+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.normalize();
    float r = ((float)rand()/RAND_MAX);
    float stepSize =((r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r))*2.0+1.0;
    
    int seg=8;
    float f1;
    float f2;
    ofVec3f end;
    float grey =0.5;
    for(int i=0;i<seg;i++)
    {
        if (i<6)
        {
            
            
            f1 =  ((float)i)/6.0  ;
            f2 =  ((float)i+1.0)/6.0;
            
        }else
        {
            f1=1;
            f2 =1;
            
        }
        
        
        float dot =normal.dot(lightDir);
        float spec  =pow(dot,16); 
        
        glColor3f(color.x*f1*dot +spec , color.y*f1*dot +spec, color.z*f1 *dot +spec);
        glVertex3f( begin.x, begin.y,begin.z);
        normal.y -=0.04*(seg-i);
        normal.normalize();
        
        
        
        
        end  = begin+ normal *stepSize;
         dot =normal.dot(lightDir);
        spec  =pow(dot,16); 
        
        glColor3f(color.x*f2*dot +spec, color.y*f2*dot +spec , color.z*f2*dot +spec);
        glVertex3f(end.x, end.y,end.z);
        
        
        begin =end;
        
    }
    //glEnd(); 
    
    
    
    
}
void KinectTriangle::drawHair( ofVec3f begin, ofVec3f normal ,ofVec3f color  )
{

  normal.x+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.y+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.z+= (((float)rand()/RAND_MAX)-0.5)*2;
    normal.normalize();
    float r = ((float)rand()/RAND_MAX);
    float stepSize =((r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r*r))*2.0+1.0;
 
    int seg=8;
    float f1;
    float f2;
    ofVec3f end;
    float grey =0.5;
    for(int i=0;i<seg;i++)
    {
        if (i<6)
        {
            

            f1 =  ((float)i)/6.0  ;
        f2 =  ((float)i+1.0)/6.0;
          
        }else
        {
            f1=1;
            f2 =1;
        
        }
  
        glColor3f(color.x*f1 , color.y*f1, color.z*f1 );
        glVertex3f( begin.x, begin.y,begin.z);
        normal.y -=0.04*(seg-i);
        normal.normalize();
        end  = begin+ normal *stepSize;
       
          
       glColor3f(color.x*f2, color.y*f2 , color.z*f2);
            glVertex3f(end.x, end.y,end.z);
        

        begin =end;
        
    }
    //glEnd(); 




}

