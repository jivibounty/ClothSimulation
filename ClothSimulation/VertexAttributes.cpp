
#include "VertexAttributes.h"
#include "OpenGLUtil.h"

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

		VertexAttributes::VertexAttributes()
		{

		}

		VertexAttributes::~VertexAttributes()
		{
			clear();
		}

		void VertexAttributes::clear()
		{
			m_vVertexAttributes.clear();
		}

		void VertexAttributes::bind()
		{
			for (unsigned int attribIndex = 0; attribIndex < m_vVertexAttributes.size(); ++attribIndex)
			{
				glEnableVertexAttribArray(m_vVertexAttributes[attribIndex].m_ShaderLocation);
				checkGLError();
				if(m_vVertexAttributes[attribIndex].m_bIsInteger)
				{
					glVertexAttribPointer(m_vVertexAttributes[attribIndex].m_ShaderLocation,
						m_vVertexAttributes[attribIndex].m_NumDataTypePerData,
						GL_FLOAT,
						GL_FALSE,
						m_vVertexAttributes[attribIndex].m_StridesInBytes,
						(char*)NULL + m_vVertexAttributes[attribIndex].m_BufferOffsetInBytes);
					checkGLError();
				}
				else
				{
					glVertexAttribIPointer(m_vVertexAttributes[attribIndex].m_ShaderLocation,
						m_vVertexAttributes[attribIndex].m_NumDataTypePerData,
						GL_INT,
						m_vVertexAttributes[attribIndex].m_StridesInBytes,
						(char*)NULL + m_vVertexAttributes[attribIndex].m_BufferOffsetInBytes);
					checkGLError();
				}
				glVertexAttribDivisor(m_vVertexAttributes[attribIndex].m_ShaderLocation, m_vVertexAttributes[attribIndex].m_InstanceDivisor);
				checkGLError();
			}
		}

		void VertexAttributes::unbind()
		{
			for (unsigned int attribIndex = 0; attribIndex < m_vVertexAttributes.size(); ++attribIndex)
			{
				glDisableVertexAttribArray(m_vVertexAttributes[attribIndex].m_ShaderLocation);
				checkGLError();
			}
		}

		void VertexAttributes::addAttribute(const SVertexAttribute& vertexAttribute)
		{
			m_vVertexAttributes.push_back(vertexAttribute);
		}

		void VertexAttributes::addAttribute(const std::string& szName, unsigned int attribLoc, unsigned int numDataTypePerData, unsigned int stridesInBytes, unsigned int bufferOffsetInBytes, bool bIsInteger)
		{
			m_vVertexAttributes.push_back(SVertexAttribute(szName, attribLoc, numDataTypePerData, stridesInBytes, bufferOffsetInBytes, bIsInteger));
		}

		unsigned int VertexAttributes::getNumberOfAttributes()
		{
			return  m_vVertexAttributes.size();
		}

		const VertexAttributes::SVertexAttribute* VertexAttributes::getAttribute(unsigned int index)
		{
			return &m_vVertexAttributes[index];
		}

	}

}
