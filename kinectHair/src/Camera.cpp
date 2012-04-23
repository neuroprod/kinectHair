//
//  Camera.cpp
//  furryKinectApp
//
//  Created by Kris Temmerman on 08/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Camera.h"


Camera* Camera::m_pSingleton = NULL;

Camera::Camera() { 
    

    perspectiveMatrix.makePerspectiveMatrix(60,(float)1, 0.1,17000);
    worldMatrix.makeLookAtViewMatrix(ofVec3f(0,0,500), ofVec3f(0,0,2500), ofVec3f(0,1,0));
 
}


Camera::~Camera() { }

Camera* Camera::getInstance()
{
    if(m_pSingleton == NULL)
        m_pSingleton = new Camera();
    
    return m_pSingleton;
}

void Camera::resize()
{
    if (ofGetHeight()==0) return;
  
    float ratio = (float)ofGetWidth()/(float)ofGetHeight();
    
    perspectiveMatrix.makePerspectiveMatrix(60,ratio, 0.1,17000);


}