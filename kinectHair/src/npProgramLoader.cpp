//
//  npProgramLoader.cpp
//  displaylist
//
//  Created by Kris Temmerman on 02/10/11.
//
//  Copyright (C) 2011 Kris Temmerman,  www.neuroproductions.be
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


#include "npProgramLoader.h"
npProgramLoader::npProgramLoader()
{
    hasGeomtryShader =false;
    
}
npProgramLoader::~npProgramLoader()
{
    
    
    
}
void npProgramLoader::useGeomtryShader( GLenum inGeomtry, GLenum outGeomtry,GLint numGeometry) 
{
    hasGeomtryShader  =true;
    geoIn = inGeomtry;
    geoOut =outGeomtry;
    geoNum =numGeometry;

}
GLuint npProgramLoader::loadProgram(string  shader )
{
    
    GLuint vertShader, fragShader;
  
    GLint logLength;
    
    program = glCreateProgram();
    
    if (hasGeomtryShader){
        glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, geoIn);
    
        glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, geoOut);
    
        glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, geoNum);
    }
    
    const GLchar *sourceV;
    sourceV=npTextFileLoader::loadChar  (shader,"vsh");
    
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &sourceV, NULL);
    glCompileShader(vertShader);
    

    
    
    
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(vertShader, logLength, &logLength, log);
        cout << "VertexShader compile log:"<<  log<< "\n";
        delete log;
    }
    
    const GLchar *sourceF;
    sourceF = npTextFileLoader::loadChar  (shader,"fsh");
    if (!sourceF)
    {
        cout << "fragment shader not found";
    }
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &sourceF, NULL);
    glCompileShader(fragShader);
    
        
    
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(fragShader, logLength, &logLength, log);
        cout << "FragmentShader compile log:"<<  log<< "\n";
        delete log;
    }
    
    glAttachShader(program, vertShader);
    
    glAttachShader(program, fragShader);
    
    
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    if (hasGeomtryShader)
    {
        GLuint geoShader;
        
        const GLchar *sourceG;
        sourceG = npTextFileLoader::loadChar  (shader,"gsh");
        if (!sourceG)
        {
            cout << "fragment shader not found";
        }
       geoShader = glCreateShader(GL_GEOMETRY_SHADER_EXT);
        glShaderSource(  geoShader, 1, &sourceG, NULL);
        glCompileShader(  geoShader);
        
        
        
        glGetShaderiv( geoShader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(fragShader, logLength, &logLength, log);
            cout << "GeoShader compile log:"<<  log<< "\n";
            delete log;
        }
        
        glAttachShader(program,  geoShader);
        
        glDeleteShader( geoShader);
      
    
    }
    
    return program;
    
}
void npProgramLoader::linkProgram()
{
    glLinkProgram(program);
    
    
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, log);
        cout << "Program link log:" << log<<"\n";
        free(log);
    }
    
    
    
    
}