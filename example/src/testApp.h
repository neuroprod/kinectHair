#pragma once

#include "ofMain.h"

#include "ofxKinect.h"
#include "ofxFBOTexture.h"
#include "KinectHandler.h"

class testApp : public ofBaseApp {
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
	
    ofCamera cam;
	
    ofxFBOTexture fbo;
	KinectHandler kinectHandler;
	
  
	int drawFaze;

	
	int angle;
	
    // used for viewing the point cloud
	ofEasyCam easyCam;
 

};
