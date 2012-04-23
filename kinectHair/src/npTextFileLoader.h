//
//  npTextFileLoader.h
//  displaylist
//
//  Created by Kris Temmerman on 01/10/11.
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

#ifndef displaylist_npTextFileLoader_h
#define displaylist_npTextFileLoader_h

#include "npIncludes.h"






class npTextFileLoader
{

public:
     static const char * loadChar(string file, string type )
    {
        string path  ="../../../"+ file+"."+type  ;
        const char *pathName = path.c_str();
        
        
        char *source = NULL;
        source = loadText(pathName );
        if (!source)  cout << endl << "ERROR: faild to load " << ofToDataPath(file+"."+type ) <<endl; 
        
        return source;
        
        
        
    }
    static  char * loadText(const char *fileName)
    {
        GLchar *shaderText = NULL;
        GLint shaderLength = 0;
        FILE *fp;
        
        fp = fopen(fileName, "r");
        
        if (fp != NULL)
        {
            while (fgetc(fp) != EOF)
            {
                shaderLength++;
            }
            rewind(fp);
            shaderText = (GLchar *)malloc(shaderLength+1);
            if (shaderText != NULL)
            {
                fread(shaderText, 1, shaderLength, fp);
            }
            shaderText[shaderLength] = '\0';
            fclose(fp);
        }else 
        {
        cout << endl << "ERROR: faild to load " <<fileName <<endl; 
        }
        
        return shaderText;
    }
   
};


#endif
