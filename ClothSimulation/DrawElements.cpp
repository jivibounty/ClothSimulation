
#include "DrawElements.h"
#include "Program.h"

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

		DrawElements::DrawElements()
			: m_BaseInstance(0)
			, m_InstanceCount(0)
			, m_DataFormat(GL_UNSIGNED_INT)
			, m_DrawMode(GL_TRIANGLES)
			, m_IndexCount(0)
			, m_IndexOffset(0)
			, m_IndexOffsetInBytes(0)
			, m_BaseVertex(0)
			, m_IndexSizeInBytes(sizeof(unsigned int))
		{

		}

		void DrawElements::draw()
		{
			glDrawElementsInstancedBaseVertexBaseInstance(m_DrawMode, m_IndexCount, m_DataFormat, (char*)NULL + m_IndexOffsetInBytes, m_InstanceCount, m_BaseVertex, m_BaseInstance);
		}

		void DrawElements::setIndexCount(unsigned int icount)
		{
			m_IndexCount = icount;
			updateIndexSizeInBytes();
		}

		void DrawElements::setIndexOffset(unsigned int ioffset)
		{
			m_IndexOffset = ioffset;
			updateIndexOffsetInBytes();
		}

		void DrawElements::setDataFormat(GLint dataFormat)
		{
			m_DataFormat = dataFormat;
			updateIndexOffsetInBytes();
			updateIndexSizeInBytes();
		}

		void DrawElements::updateIndexOffsetInBytes()
		{
			if (m_DataFormat == GL_UNSIGNED_BYTE)
			{
				m_IndexOffsetInBytes = m_IndexOffset * sizeof(unsigned char);
			}
			else if (m_DataFormat == GL_UNSIGNED_SHORT)
			{
				m_IndexOffsetInBytes = m_IndexOffset * sizeof(unsigned short);
			}
			else
			{
				m_IndexOffsetInBytes = m_IndexOffset * sizeof(unsigned int);
			}
		}

		void DrawElements::updateIndexSizeInBytes()
		{
			if (m_DataFormat == GL_UNSIGNED_BYTE)
			{
				m_IndexSizeInBytes = m_IndexCount * sizeof(unsigned char);
			}
			else if (m_DataFormat == GL_UNSIGNED_SHORT)
			{
				m_IndexSizeInBytes = m_IndexCount * sizeof(unsigned short);
			}
			else
			{
				m_IndexSizeInBytes = m_IndexCount * sizeof(unsigned int);
			}
		}

	}

}
