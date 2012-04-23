//
//  Shader.vsh
//  mbcarconfig
//
//  Created by Kris Temmerman on 20/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#version 120
#extension GL_EXT_geometry_shader4 : enable


uniform mat4 worldMatrix;
uniform mat4 perspMatrix;


varying in vec3 N [];
varying in vec3 C  [];
varying out vec3 gsNormal;
varying out vec3 gsColor;

void main()
{
    float lFactor =0.5;
  
    vec4 p0 = gl_PositionIn[0] ;
    vec3 normal = N [0];
    vec3 color =C  [0];
    
    
    //point 1
    gl_Position =perspMatrix* p0;
    gsNormal =normal;
    gsColor =color;
	EmitVertex();
  
    
    
    //point 2
    p0.x+=2.0* lFactor;
    
    gl_Position =perspMatrix* p0;
    gsNormal =normal;
    gsColor =color;
	EmitVertex();
    
    //point 3
    normal.y-=0.2;
    normalize(normal);
    p0.xyz +=normal*10.0;
    p0.x-=2.0;
 
    gl_Position =perspMatrix* p0;
    gsNormal =normal;
    gsColor =color;
	EmitVertex();
   
    //point 4
    normal.y-=0.2;
    normalize(normal);
    p0.x+=0.0;
    p0.xyz +=normal*10.0;
    
    gl_Position =perspMatrix* p0;
    gsNormal =normal;
    gsColor =color;
	EmitVertex();
    
    
    //point 5
    normal.y-=0.4;
    normalize(normal);
    p0.xyz +=normal*6.0* lFactor;
    
    gl_Position =perspMatrix* p0;
    gsNormal =normal;
    gsColor =color;
	EmitVertex();
    

}
