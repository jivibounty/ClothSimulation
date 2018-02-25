
#pragma once



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

		class DrawElements
		{
		protected:
			unsigned int m_BaseInstance;
			unsigned int m_InstanceCount;
			unsigned int m_IndexCount;
			unsigned int m_IndexOffset;
			unsigned int m_IndexOffsetInBytes;
			unsigned int m_IndexSizeInBytes;
			unsigned int m_BaseVertex;
			GLenum m_DrawMode;
			GLint m_DataFormat;
		public:
			DrawElements();
			~DrawElements(){}
			virtual void clear() {}
			virtual void draw();
			virtual void setInstanceCount(unsigned int instanceCount) { m_InstanceCount = instanceCount; }
			virtual unsigned int getInstanceCount() const { return m_InstanceCount; }
			virtual void setBaseInstance(unsigned int baseInstance) { m_BaseInstance = baseInstance; }
			virtual unsigned int getBaseInstance() const { return m_BaseInstance; }
			virtual void setIndexCount(unsigned int icount);
			virtual unsigned int getIndexCount() const { return m_IndexCount; }
			virtual void setIndexOffset(unsigned int ioffset);
			virtual unsigned int getIndexOffsetInBytes() const { return m_IndexOffsetInBytes; }
			virtual void setIndexSizeInBytes(unsigned int size){ m_IndexSizeInBytes = size; }
			virtual unsigned int getIndexOffset() const { return m_IndexOffset; }
			virtual void setDrawMode(GLenum drawMode) { m_DrawMode = drawMode; }
			virtual GLenum getDrawMode() { return m_DrawMode; }
			virtual void setDataFormat(GLint dataFormat);
			virtual GLint getDataFormat() { return m_DataFormat; }
			virtual void setBaseVertex(unsigned int baseVertex) { m_BaseVertex = baseVertex; }
			virtual unsigned int getBaseVertex() const { return m_BaseVertex; }
		protected:
			virtual void updateIndexOffsetInBytes();
			virtual void updateIndexSizeInBytes();

		};

	}

}
