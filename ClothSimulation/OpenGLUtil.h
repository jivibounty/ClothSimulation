
#pragma once

#ifdef _MSC_VER  // Check if MS Visual C compiler
#pragma comment(lib, "opengl32.lib")  // Compiler-specific directive to avoid manual configuration
#pragma comment(lib, "glu32.lib")    // Link libraries
#pragma comment(lib, "glew32.lib")    // Link libraries
#endif

#ifndef MACOSX
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <stdio.h>

namespace Bounty
{
	namespace OpenGL
	{

#ifdef _DEBUG
#	define checkGLError()													\
		{																	\
		GLenum err = glGetError();			                            \
		if (err != GL_NO_ERROR) {										\
		fprintf(stderr, "\nOpenGL Error: %s\nFile: %sLine: %d\n",	\
		gluErrorString(err), __FILE__, __LINE__);					\
		fflush(stderr);												\
		}																\
	}																	
#else
#	define checkGLError()
#endif

	}

}
