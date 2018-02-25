
#include "BufferObject.h"
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

#include <stdlib.h>

namespace Bounty
{
	namespace OpenGL
	{

		BufferObject::BufferObject()
			: m_Usage(GL_STATIC_DRAW)
			, m_Target(GL_ARRAY_BUFFER)
			, m_BufferIndex(0)
		{
		}

		BufferObject::~BufferObject()
		{
			clear();
		}

		void BufferObject::clear()
		{
			if (m_BufferIndex > 0)
			{
				glDeleteBuffersARB(1, &m_BufferIndex);
				checkGLError();
				m_BufferIndex = 0;
			}
		}

		void BufferObject::bind()
		{
			glBindBufferARB(m_Target, m_BufferIndex);
			checkGLError();
		}

		void BufferObject::bindRange(unsigned int bindingIndex, void* offset, int size)
		{
			glBindBufferRange(m_Target, bindingIndex, m_BufferIndex, (GLintptr)offset, size);
			checkGLError();
		}

		void BufferObject::bindBase(unsigned int bindingIndex)
		{
			glBindBufferBase(m_Target, bindingIndex, m_BufferIndex);
			checkGLError();
		}

		void BufferObject::unbind()
		{
			glBindBufferARB(m_Target, 0);
			checkGLError();
		}

		bool BufferObject::create(GLenum target, void *data, int dataSize, int dataTypeSize, GLenum usage)
		{
			clear();
			if (!glGenBuffersARB)
			{
				return false;
			}
			glGenBuffersARB(1, &m_BufferIndex);
			checkGLError();
			m_Target = target;
			m_Usage = usage;
			return update(data, dataSize, dataTypeSize);
		}

		bool BufferObject::update(void *data, int dataSize, int dataTypeSize)
		{
			if (m_BufferIndex != 0 && dataSize != 0 && dataTypeSize != 0)
			{
				glBindBufferARB(m_Target, m_BufferIndex);
				checkGLError();
				glBufferDataARB(m_Target, dataSize * dataTypeSize, data, m_Usage);
				checkGLError();
				glBindBufferARB(m_Target, 0);
				checkGLError();
			}
			return true;
		}

		bool BufferObject::update(void *data, int offset, int dataSize, int dataTypeSize)
		{
			if (m_BufferIndex != 0 && dataSize != 0 && dataTypeSize != 0)
			{
				glBindBufferARB(m_Target, m_BufferIndex);
				checkGLError();
				glBufferSubDataARB(m_Target, offset, dataSize * dataTypeSize, data);
				checkGLError();
				glBindBufferARB(m_Target, 0);
				checkGLError();
			}
			return true;
		}

		unsigned int BufferObject::getBufferIndex() const
		{
			return m_BufferIndex;
		}

	}

}
