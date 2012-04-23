//
//  Shader.fsh
//  mbcarconfig
//
//  Created by Kris Temmerman on 20/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//







varying  vec3 gsNormal;
varying  vec3 gsColor;
void main()
{
   float dot =clamp(dot(gsNormal,vec3(0.19245, 0.19245, 0.96225)),0.0,1.0);
   float  spec  =pow(dot,32.0); 
    vec3 c = dot*gsColor +spec*2.0;
   
    gl_FragColor = vec4(c  ,1.0);

}
