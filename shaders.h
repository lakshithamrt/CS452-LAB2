#ifndef SHADERS_H_
#define SHADERS_H_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "Angel.h"


#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"

using namespace std; // new type for the shader information

 typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

// declaration of functions used in the program
GLuint createshaders(GLenum type, const GLchar* shadeSource);
const GLchar* ReadShader(const char* filename);
GLuint shaderprogram(const vector<GLuint> shadeList);


//-----------------------------------------------------------------------------------
// reading content in shader files
const GLchar* ReadShader(const char* filename){
	// Open the file
	FILE* fp = fopen(filename, "r");

	// Go to the beginning and get the length of the file
	fseek (fp, 0, SEEK_END);
	long file_length = ftell(fp);

	// Go back to the beginning and read the contents
	fseek (fp, 0, SEEK_SET);
	GLchar* contents = new GLchar[file_length+1];
	for (int i = 0; i < file_length+1; i++) {
		contents[i] = 0;
	}
	fread (contents, 1, file_length, fp);
	contents[file_length] = '\0';
	fclose(fp);

	return const_cast<const GLchar*>(contents);	
}

//----------------------------------------------------------------------------
// function responsible for coordinating shader creation process
GLuint BuildShader(ShaderInfo* shaders){ 
	
	ShaderInfo* shade=shaders;
  
    vector<GLuint> Shadelist;

    while(shade->type != GL_NONE){//loop through all the shaders in the list
    Shadelist.push_back(createshaders(shade->type, ReadShader(shade->filename)));//adding shaders into the list
    ++shade;//incrementation
  }
  GLuint program=shaderprogram(Shadelist);//creates the program linking to all the shaders
  glUseProgram(program);

}


//---------------------------------------------------------------------------
//compile content which returned by reading function

GLuint createshaders(GLenum shadertype, const GLchar* source){


	GLuint program = glCreateProgram();

	//create and compiled the shaders
	GLuint fshader = glCreateShader(shadertype);
	glShaderSource(fshader, 1, &source, NULL);
	glCompileShader(fshader);  

	 GLint compiled;
     glGetShaderiv( fshader, GL_COMPILE_STATUS, &compiled );
     if ( !compiled ) 
	    std::cerr<< " failed to compile:" << std::endl;


	return fshader;
  

}

//--------------------------------------------------------------------------
//Attaching the shaders with program and linking 
GLuint shaderprogram(const vector<GLuint> shaderlist){


  GLuint program = glCreateProgram();//creates your program

  
  for(GLuint i=0;i<shaderlist.size();i++){
  glAttachShader(program,shaderlist[i]);


  }//attaches shaders to program
  
  glLinkProgram(program); // link the shaders with program
  return program;

}

#endif
