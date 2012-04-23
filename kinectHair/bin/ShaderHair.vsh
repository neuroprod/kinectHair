//
//  Shader.vsh
//  mbcarconfig
//
//  Created by Kris Temmerman on 20/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#version 120


attribute vec4 position;
attribute vec3 normal;
attribute vec3 color;



uniform mat4 worldMatrix;
uniform mat4 perspMatrix;

varying vec3 N ;
varying vec3 C ;

void main()
{
 
  
   
    vec4 worldSpace = worldMatrix* position;
    gl_Position =worldSpace ;
    
   N  =normalize( normal);
    C = color;
   
}
