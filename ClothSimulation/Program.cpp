
#include "Program.h"
#include "Shader.h"
#include "OpenGLUtil.h"
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

		Program::Program()
			: m_ProgramHandle(0)
			, m_bIsDirty(false)
			, m_bIsValidated(true)
		{

		}

		Program::~Program()
		{
			clear();
		}

		void Program::clear()
		{
			if (m_ProgramHandle != 0)
			{
				glDeleteProgram(m_ProgramHandle);
				m_ProgramHandle = 0;
			}
			for (auto itr = m_vShaders.begin(); itr != m_vShaders.end(); ++itr)
			{
				itr->clear();
			}
			m_vShaders.clear();
		}

		void Program::addShader(const Shader& shader)
		{
			m_vShaders.push_back(shader);
			m_bIsDirty = true;
			m_bIsValidated = false;
		}

		void Program::addShader(GLenum shaderType, const std::string& szShaderString)
		{
			Shader shader;
			shader.setShaderType(shaderType);
			shader.setShaderString(szShaderString);
			addShader(shader);
		}

		unsigned int Program::getNumberOfShaders() const
		{
			return m_vShaders.size();
		}

		void Program::bind()
		{
			if (isDirty())
			{
				compileProgram();
			}
			glUseProgram(m_ProgramHandle);
		}

		void Program::unbind()
		{
			glUseProgram(0);
		}

		bool Program::isValidated()
		{
			if (m_bIsValidated)
			{
				return true;
			}
			if (isDirty())
			{
				return false;
			}
			glValidateProgram(m_ProgramHandle);
			checkGLError();
			GLint programValidationStatus = GL_FALSE;
			glGetProgramiv(m_ProgramHandle, GL_VALIDATE_STATUS, &programValidationStatus);
			checkGLError();

			if (programValidationStatus == GL_FALSE)
			{
				fprintf(stderr, "Error: could not validate program\n");
				displayProgramError(m_ProgramHandle);
				return false;
			}
			m_bIsValidated = true;
			return true;
		}

		GLint Program::getParameter(const std::string& szName)
		{
			if (isDirty())
			{
				compileProgram();
			}
			GLint uniformLocation = glGetUniformLocation(m_ProgramHandle, szName.c_str());
			checkGLError();
			if (uniformLocation < 0)
			{
				fprintf(stderr, "\nCant find Uniform Location for %s in Program %d\n", szName.c_str(), m_ProgramHandle);
			}
			return uniformLocation;
		}

		GLuint Program::getBlockParameter(const std::string& szName)
		{
			if (isDirty())
			{
				compileProgram();
			}
			GLuint uniformLocation = glGetUniformBlockIndex(m_ProgramHandle, szName.c_str());
			checkGLError();
			if (uniformLocation == GL_INVALID_INDEX)
			{
				fprintf(stderr, "\nCant find Uniform Block Location for %s in Program %d\n", szName.c_str(), m_ProgramHandle);
			}
			return uniformLocation;
		}

		void Program::setParameterBlockIndex(GLuint blockIndex, GLuint bindingIndex)
		{
			glUniformBlockBinding(m_ProgramHandle, blockIndex, bindingIndex);
			checkGLError();
		}

		void Program::setAttributeIndex(GLint index, const std::string& szName)
		{
			glBindAttribLocation(m_ProgramHandle, index, szName.c_str());
			checkGLError();
		}

		GLint Program::getAttributeIndex(const std::string& szName)
		{
			GLint index = glGetAttribLocation(m_ProgramHandle, szName.c_str());
			checkGLError();
			return index;
		}

		void Program::setFragmentOutputIndex(GLint index, const std::string& szName)
		{
			glBindFragDataLocation(m_ProgramHandle, index, szName.c_str());
			checkGLError();
		}

		GLint Program::getFragmentOutputIndex(const std::string& szName)
		{
			GLint index = glGetFragDataLocation(m_ProgramHandle, szName.c_str());
			checkGLError();
			return index;
		}

		void Program::compileProgram()
		{
			if (m_ProgramHandle != 0)
			{
				glDeleteProgram(m_ProgramHandle);
				m_ProgramHandle = 0;
			}
			for (auto itr = m_vShaders.begin(); itr != m_vShaders.end(); ++itr)
			{
				load(*itr);
			}
			if (m_ProgramHandle == 0)
			{
				return;
			}
			glLinkProgram(m_ProgramHandle);
			checkGLError();
			GLint programLinkStatus = GL_FALSE;
			glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &programLinkStatus);
			checkGLError();

			if (programLinkStatus == GL_FALSE)
			{
				fprintf(stderr, "Error: could not link program\n");
				displayProgramError(m_ProgramHandle);
				return;
			}
			setDirty(false);
		}

		bool Program::load(Shader& shader)
		{
			if (m_ProgramHandle == 0)
			{
				m_ProgramHandle = glCreateProgram();
				checkGLError();
			}
			if (m_ProgramHandle == 0)
			{
				return false;
			}
			GLhandleARB shaderHandle = glCreateShader(shader.getShaderType());
			shader.setShaderHandle(shaderHandle);
			checkGLError();
			const GLchar* szShaderString = shader.getShaderString().c_str();
			glShaderSource(shaderHandle, 1, const_cast<const GLchar**>(&szShaderString), NULL);
			checkGLError();
			glCompileShader(shaderHandle);
			checkGLError();
			GLint shaderStatus = GL_FALSE;
			glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &shaderStatus);
			checkGLError();

			if (shaderStatus == GL_FALSE)
			{
				displayShaderError(shaderHandle);
				glDeleteShader(shaderHandle);
				return false;
			}
			shader.setShaderHandle(shaderHandle);
			glAttachShader(m_ProgramHandle, shaderHandle);
			checkGLError();
			return true;
		}

		void Program::displayProgramError(GLhandleARB handle)
		{
			if (handle == 0)
			{
				fprintf(stderr, "Error: Could not display error: Invalid object handle\n");
			}
			GLint programInfoLen = 0;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &programInfoLen);
			checkGLError();
			if (programInfoLen > 1)
			{
				char* programInfoLog = new char[programInfoLen];
				if (programInfoLog == NULL)
				{

					fprintf(stderr, "Error: Could not display error: Program out of memory\n");
					return;
				}
				glGetProgramInfoLog(handle, programInfoLen, NULL, programInfoLog);
				checkGLError();
				fprintf(stderr, "Error: %s\n", programInfoLog);
				delete[] programInfoLog;
			}
		}

		void Program::displayShaderError(GLhandleARB handle)
		{
			if (handle == 0)
			{
				fprintf(stderr, "Error: Could not display error: Invalid object handle\n");
			}
			GLint programInfoLen = 0;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &programInfoLen);
			checkGLError();
			if (programInfoLen > 1)
			{
				char* programInfoLog = new char[programInfoLen];
				if (programInfoLog == NULL)
				{

					fprintf(stderr, "Error: Could not display error: Program out of memory\n");
					return;
				}
				glGetShaderInfoLog(handle, programInfoLen, NULL, programInfoLog);
				checkGLError();
				fprintf(stderr, "Error: %s\n", programInfoLog);
				delete[] programInfoLog;
			}
		}

		void Program::setDirty(bool bIsDirty)
		{
			m_bIsDirty = bIsDirty;
		}

	}

}
