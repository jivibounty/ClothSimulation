
#pragma once


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

namespace Bounty
{
	namespace OpenGL
	{

		class BufferObject
		{
		public:
			BufferObject();
			~BufferObject();
			virtual void clear();
			virtual void bind();
			virtual void bindRange(unsigned int bindingIndex, void* offset, int size);
			virtual void bindBase(unsigned int bindingIndex);
			virtual void unbind();
			virtual bool create(GLenum target, void *data, int dataSize, int dataTypeSize, GLenum usage);
			virtual bool update(void *data, int dataSize, int dataTypeSize);
			virtual bool update(void *data, int offset, int dataSize, int dataTypeSize);
			virtual unsigned int getBufferIndex() const;
		protected:
			GLenum m_Usage;
			GLuint m_BufferIndex;
			GLenum m_Target;
		};

	}

}
