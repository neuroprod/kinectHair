//
//  FurryKinectApp.cpp
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

#include "FurryKinectApp.h"
#include <stdio.h>

//--------------------------------------------------------------
void FurryKinectApp::setup() {
	
    // setup the kinect
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
    // set the start angle of the kinnect
    angle = 0;
	kinect.setCameraTiltAngle(angle);
    
    
    
    // setup the Openframeworks background color and the framerate
    ofBackground(255, 255, 255);
    ofSetFrameRate(60);
	// we don't want to clear the colorbuffer automaticly, only when we have new kinect data
    ofSetBackgroundAuto(false); 
    glEnable(GL_DEPTH_TEST);
	    
    
    //the KinectDepthTriangulation class makes a triangle mesh from the kinect data
    // It uses a marching squares algoritme for the triangulistation
    // the gridSubH and gridSubW are the number of horizontal and vertical grid lines
    // the min and the max distance is the range in milimetres that gets triangulated
    //
    // it generates trinagle objects, but also a vertices and indices array
    //
    // You can change the depth range at runtime
    // setDepthRange(float minDepth,float maxDepth);
    const int gridSubH =128;
    const int gridSubW = 96; 
     minDistance =600;
     maxDistance = 2000;
    triangulate.setup(gridSubH,gridSubW, minDistance,maxDistance);
    
    
    // the KinectHairPoints class calculates the startpoints for the hairs, by subdeviding the triangles it gets from the KinectDepthTriangulation
    // the setup takes the number of hairs that get generated for each triangle
    hairPoints.setup(30);
	useRealColors =false;

   
  
    // the hair rendere is responsible for creating and rendering the hairs
    // it useses the KinectHairPoints output (vertices and normals) to create a tringle strip for each hair using a geomtry shader
    hairRenderer.setup();
    
    
    // the tri renderer  renders the triangle output of the KinectDepthTriangulation behind the hairs, incase whe have holes in there
    triRenderer.setup();
    //
    
    indices =0;
    vertices =0;
    isDirty =false;
 
}

//--------------------------------------------------------------
void FurryKinectApp::update() {
	
	
	// update the kinect
    kinect.update();
    
  
    if(kinect.isFrameNew()) {
        // if whe have new kinect data, we set the isDirty to treu, so we know we have to update the output graphics
        isDirty =true;
        
   
       
        //kinectHandler.setColorPixels(kinect.getPixels());
        
        // the triangulate class takes the raw depth output of the kinect
        // note: you don't nesesarly have to use the ofKinect addon, you can use it with every kinect framework 
        triangulate.setRawPixels(kinect.getDistancePixels());
        
        // we normalize the normals of the vertices
        // note: for the hairs we need them strait away, but if you use just the triangles, its more economic to normalise the normals in your shader 
        triangulate.normalizeVertexNormals();
        
        
     
        if( useRealColors)
        {
            // uses the original colors of the kinect camera
             hairPoints.setHairColors(kinect.getPixels());
        
        }else
        {
            // set a single hair color (the hairpoint class ads some variation to the color)
            hairPoints.setHairColor(30,30,30);
        }
        // we pass the triangles to the KinectHairPoints class  
        hairPoints.setTriangles( triangulate.triangles);
      
        
        // prepares the data from the KinectTriangulate to use in the triangle mesh renderer
        prepTriData();
        
        
    }
	
        
}
void FurryKinectApp::prepTriData()
{
    // takes the generated indices and the vertices of KinectTriangulistaion class and puts them in arrays, so they can get pased to opengl
    numIndices =  triangulate.indices.size();
    uint *tempIndices = new uint[numIndices];
    int i;
    for (i =0 ;i<numIndices;i++)
    {
        tempIndices[i] = triangulate.indices[i ];
        
    }
    delete [] indices;
    indices = tempIndices;
    
    
    
   numVertices =  triangulate.vertices.size();
    float *tempVertices = new float [numVertices *6];
    int count =0;
    for (i =0 ;i<numVertices;i++)
    {
        
        TriPoint *v=   &triangulate.vertices[i ];
        tempVertices[count] =v->x;
        count++;
        tempVertices[count] =v->y;
        count++;
        tempVertices[count] =v->z;
        count++;
        
        tempVertices[count] =v->xn;
     
        count++;
        tempVertices[count] =v->yn;
        count++;
        tempVertices[count] =v->zn;
        count++;
    }
    delete [] vertices;
    vertices= tempVertices;
  

}
//--------------------------------------------------------------
void FurryKinectApp::draw() {
    
	if (!isDirty) return;  // no need to redaw when the kinect hasn't updated;
    isDirty =false;
    
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    
    glDisable(GL_DEPTH_TEST);
    //draws the background 
    //we dont need a depth test for that, and we dont want the backgroud depth to interfere with the depth of the hairs
    triRenderer.draw(vertices, indices, numIndices);
    
    glEnable (GL_DEPTH_TEST);
    // draw the hairs
    hairRenderer.draw ( hairPoints.data,hairPoints. numIndices);


    //ofDrawBitmapString("fps: " + ofToString((int)ofGetFrameRate()) , 20, 20);
}



//--------------------------------------------------------------
void FurryKinectApp::exit() {
	
	kinect.close();
	

}

//--------------------------------------------------------------
void FurryKinectApp::keyPressed (int key) {
    
   	switch (key) {
        case 115:
            //s   create a screenshot
            {   
                string fileName;
                fileName = "screenshot"+ofToString(ofGetElapsedTimeMillis()) +".png";
                ofSaveScreen(fileName);
            }
            
			break;    
        case 32:
            //space
            useRealColors =!useRealColors;
			break;
            
        case 49:
            //1
            minDistance -=100;
            if (minDistance<100) minDistance =100;
            triangulate.setDepthRange(minDistance, maxDistance);
			break;    
        case 50:
            //2
            minDistance +=100;
            if (minDistance>maxDistance -100) maxDistance -100;
              triangulate.setDepthRange(minDistance, maxDistance);
            
			break;   
        case 51:
            //3
            maxDistance -=100;
            if (maxDistance<minDistance+100) maxDistance =minDistance+100;
              triangulate.setDepthRange(minDistance, maxDistance);
			break;   
        case 52:
            //4
            maxDistance +=100;
            if (maxDistance>7000) maxDistance =7000;
              triangulate.setDepthRange(minDistance, maxDistance);
			break;   
            
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
	}
}

//--------------------------------------------------------------
void FurryKinectApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void FurryKinectApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void FurryKinectApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void FurryKinectApp::windowResized(int w, int h)
{

    Camera::getInstance()->resize();

}
