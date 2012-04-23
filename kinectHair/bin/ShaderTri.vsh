//
//  Shader.vsh
//  mbcarconfig
//
//  Created by Kris Temmerman on 20/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute vec4 normal;




uniform mat4 worldMatrix;
uniform mat4 perspMatrix;




void main()
{
 
  
   
    vec4 worldSpace = worldMatrix* (position+vec4(normal.xyz*00.0,0.0));
    gl_Position =perspMatrix*worldSpace ;
    
   
  
   
}
