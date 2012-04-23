//
//  HairRenderer.cpp
//  furryKinectApp
//
//  Created by Kris Temmerman on 08/04/12.
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

#include "HairRenderer.h"
#include "npProgramLoader.h"
#include "GLErrorCheck.h"
enum {
    ATTRIB_VERTEX_FS,
    ATTRIB_NORMAL_FS,
     ATTRIB_COLOR_FS
};

void HairRenderer::setup()
{
    cam  =Camera::getInstance();
    
    // setup the program 
    
    npProgramLoader ploader;
    ploader.useGeomtryShader(GL_POINTS,GL_TRIANGLE_STRIP,5)  ; 
    program  =ploader.loadProgram("ShaderHair");
    
    
    glBindAttribLocation(  program, ATTRIB_VERTEX_FS, "position");
    glBindAttribLocation(  program, ATTRIB_NORMAL_FS, "normal");
    glBindAttribLocation(  program, ATTRIB_COLOR_FS, "color");
    ploader.linkProgram();
    glUseProgram( program);
  
    uPerspectiveMatrix =glGetUniformLocation(program, "perspMatrix");
    uWorldMatrix= glGetUniformLocation(program, "worldMatrix");
    
    glUseProgram(0);
	
    
}

void HairRenderer::draw(float * data, int num ) 
{
    // render the hairs;
    glUseProgram(program);
    
    glUniformMatrix4fv(uWorldMatrix, 1, 0,   cam->worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam->perspectiveMatrix.getPtr());
    
    
    glEnableVertexAttribArray(ATTRIB_VERTEX_FS);
    glEnableVertexAttribArray(ATTRIB_NORMAL_FS);
    
    
    GLfloat *pointer =data;
    glVertexAttribPointer(ATTRIB_VERTEX_FS, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), pointer);
    glEnableVertexAttribArray(ATTRIB_VERTEX_FS);
    
    pointer +=3;
    glVertexAttribPointer(ATTRIB_NORMAL_FS, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), pointer);
    glEnableVertexAttribArray(ATTRIB_NORMAL_FS);
    
    pointer +=3;
    glVertexAttribPointer(ATTRIB_COLOR_FS, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), pointer);
    glEnableVertexAttribArray(ATTRIB_COLOR_FS);
    
    
    glDrawArrays(GL_POINTS,0, num);  
  
    
    glDisableVertexAttribArray(ATTRIB_VERTEX_FS);
    glDisableVertexAttribArray(ATTRIB_NORMAL_FS);
    GLErrorCheck::test ("&");
    
    glUseProgram(0);

}
