#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	   ofSetBackgroundAuto(false); 
    // enable depth->rgb image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	 // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	kinect.open();
	kinect.setDepthClipping(0,1000);
 

		
	ofSetFrameRate(60);
	
	// zero the tilt on startup
	angle = 20;
	kinect.setCameraTiltAngle(angle);
	kinectHandler.setup();
    kinectHandler.kin=&kinect;
    	drawFaze =0;
ofBackground(255, 255, 255);
    
    
    
    
 fbo.allocate(2048,2048,GL_RGB,8);
    fbo.bindAsTexture();
}

//--------------------------------------------------------------
void testApp::update() {
	
	//ofBackground(0, 0, 0);
	
	   if(drawFaze ==0) kinect.update();
	
	// there is a new frame and we are connected
    if(drawFaze ==1){
        if(kinect.isFrameNew()) {
	  kinectHandler.setColorPixels(kinect.getPixels());
            kinectHandler.setRawPixels(kinect.getRawDepthPixels());
            ofBackground(255, 255, 255);
            drawFaze =2;
            
         
        }
	}
    if (ofGetFrameNum() ==240 )ofBackground(255, 0, 0);
    if (ofGetFrameNum() ==300 )
    { drawFaze =1;
    ofSetBackgroundAuto(false);
    }

}

//--------------------------------------------------------------
void testApp::draw() {
	
   
    if (drawFaze ==0){
        ofSetColor(255, 255, 255);
	
			// draw from the live kinect
		kinect.drawDepth(0, 0, 640, 480);
		kinect.draw(640, 0, 640, 480);
		
	
	
        kinectHandler.draw();

	
	// draw instructions
        ofSetColor(255, 255, 255);
        stringstream reportStream;
   
    }
    if (drawFaze ==2)
    {
        ofSetColor(255, 255, 255);
        cam.begin();
       kinectHandler.draw();
        cam.end();
    
    }if(drawFaze ==4)
    {
         ofSetColor(255, 255, 255);
       fbo.begin();
        
        ofBackground(255,255, 255,255);
        
   
        // kinect.draw(-160, 0, 640*2.1, 480*2.1);
        glEnable(GL_DEPTH_TEST);
        

        kinectHandler.drawHair();
      
        fbo.end();
        
       ofSetColor(255, 255, 255);
       fbo.draw(0, 0,1024, 1024);
        drawFaze =5;
        
    }
}



//--------------------------------------------------------------
void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
				case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
        case 'a':
			if ( drawFaze ==0)
            {
                drawFaze =1;
                ofSetBackgroundAuto(false);
            }  	else 
            {
                drawFaze =0;
                ofSetBackgroundAuto(false);
            } 
			break;
        case 'r':
			if(drawFaze==2)
            {
              
             
                kinectHandler.drawStep =0;
                drawFaze =4;
            }
			break;
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
			
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
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
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}
