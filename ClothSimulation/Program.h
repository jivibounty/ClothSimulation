
#pragma once

#include <string>
#include <vector>
#ifndef MACOSX
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif


#include "Shader.h"

namespace Bounty
{
	namespace OpenGL
	{

		class Program
		{
		public:
			Program();
			~Program();
			GLhandleARB getProgramHandle() const { return m_ProgramHandle; }
			void addShader(const Shader& shader);
			void addShader(GLenum shaderType, const std::string& szShaderString);
			unsigned int getNumberOfShaders() const;
			void clear();
			void bind();
			void unbind();
			bool isValidated();
			GLint getParameter(const std::string& szName);
			GLuint getBlockParameter(const std::string& szName);
			void setParameterBlockIndex(GLuint blockIndex, GLuint bindingIndex);
			void setAttributeIndex(GLint index, const std::string& szName);
			GLint getAttributeIndex(const std::string& szName);
			void setFragmentOutputIndex(GLint index, const std::string& szName);
			GLint getFragmentOutputIndex(const std::string& szName);
		protected:
			void compileProgram();
			bool load(Shader& shader);
			void displayProgramError(GLhandleARB handle);
			void displayShaderError(GLhandleARB handle);
			void setDirty(bool bIsDirty);
			bool isDirty() const { return m_bIsDirty; }
		protected:
#pragma warning ( push )
#pragma warning ( disable : 4251 ) 
			std::vector<Shader> m_vShaders;
#pragma warning ( pop )
			bool m_bIsValidated;
			bool m_bIsDirty;
			GLhandleARB m_ProgramHandle;
		};

	}

}

