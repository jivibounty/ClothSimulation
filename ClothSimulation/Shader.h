
#pragma once


#include <string>
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

		class Shader
		{
		protected:
#pragma warning ( push )
#pragma warning ( disable : 4251 ) 
			std::string m_szShader;
#pragma warning ( pop )
			GLenum m_ShaderType;
			GLhandleARB m_ShaderHandle;
		public:
			Shader();
			~Shader();
			void clear();
			void loadShaderFromFile(const std::string& szFilename, GLenum shaderType);
			void setShaderType(GLenum type) { m_ShaderType = type; }
			GLenum getShaderType() const { return m_ShaderType; }
			void setShaderString(const std::string& szString) { m_szShader = szString; }
			const std::string& getShaderString() const { return m_szShader; }
			void setShaderHandle(GLhandleARB handle);
			GLhandleARB getShaderHandle() const { return m_ShaderHandle; }
		};

	}

}
