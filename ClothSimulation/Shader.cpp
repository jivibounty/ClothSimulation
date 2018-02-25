
#include "Shader.h"
#include <stdio.h>

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

namespace Bounty
{
	namespace OpenGL
	{

		Shader::Shader()
			: m_szShader("")
			, m_ShaderType(GL_VERTEX_SHADER)
			, m_ShaderHandle(0)
		{}

		Shader::~Shader()
		{
			clear();
		}

		void Shader::loadShaderFromFile(const std::string& szFilename, GLenum shaderType)
		{
			setShaderType(shaderType);
			FILE *pFile = NULL;
			pFile = fopen(szFilename.c_str(), "rb");
			if (pFile == NULL)
			{
				printf("Shader::loadShaderFromFile Error: could not load shader file: %s\n", szFilename.c_str());
				return;
			}
			fseek(pFile, 0, SEEK_END);
			long size = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);
			char* pData = new char[size + 1];
			memset(pData, 0, sizeof(char)* size);
			fread(pData, 1, size, pFile);
			fclose(pFile);
			pData[size] = 0;
			std::string szShaderString = pData;
			delete [] pData;
			if (szShaderString.empty())
			{
				printf("Shader::loadShaderFromFile Error: shader file is empty: %s\n", szFilename.c_str());
				return;
			}
			setShaderString(szShaderString);
		}

		void Shader::clear()
		{
			if (m_ShaderHandle != 0)
			{
				glDeleteShader(m_ShaderHandle);
				m_ShaderHandle = 0;
			}
		}

		void Shader::setShaderHandle(GLhandleARB handle)
		{
			if (m_ShaderHandle != 0 && m_ShaderHandle != handle)
			{
				clear();
			}
			m_ShaderHandle = handle;
		}

	}

}
