/******************************************************************************

 @File         OGLES3BinaryShader.cpp

 @Title        OGLES3BinaryShader

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independant

 @Description  Shows how to use extension GL_OES_get_program_binary (if
               supported) to save a compiled shader out as a binary file and then
               load it back in on future runs. It displays a red triangle if
               forced to compile shaders and displays a green triangle if using binary shaders.

******************************************************************************/
#include <stdio.h>
#include <string.h>

#include <GLES3/gl3.h>

#include <EGL/egl.h>
#define PVRGetProcAddress(x) eglGetProcAddress(#x)

#include "PVRShell.h"

/******************************************************************************
 Defines
******************************************************************************/

// Index to bind the attributes to vertex shaders
#define VERTEX_ARRAY	0

/*!****************************************************************************
 To use the shell, you have to inherit a class from PVRShell
 and implement the five virtual functions which describe how your application
 initializes, runs and releases the ressources.
******************************************************************************/
class OGLES3BinaryShader : public PVRShell
{
	// The vertex and fragment shader OpenGL handles
	GLuint m_uiVertexShader, m_uiFragShader;

	// The program object containing the 2 shader objects
	GLuint m_uiProgramObject;

	// VBO handle
	GLuint m_ui32Vbo;

	//Binary Handling functions to load and save a program.
	bool saveBinaryProgram(const char* Filename, GLuint &ProgramObjectID);
	bool loadBinaryProgram(const char* Filename, GLuint &ProgramObjectID);

public:

	virtual bool InitApplication();
	virtual bool InitView();
	virtual bool ReleaseView();
	virtual bool QuitApplication();
	virtual bool RenderScene();
};


/*!****************************************************************************
 @Function		InitApplication
 @Return		bool		true if no error occured
 @Description	Code in InitApplication() will be called by PVRShell once per
				run, before the rendering context is created.
				Used to initialize variables that are not dependant on it
				(e.g. external modules, loading meshes, etc.)
				If the rendering context is lost, InitApplication() will
				not be called again.
******************************************************************************/
bool OGLES3Bin