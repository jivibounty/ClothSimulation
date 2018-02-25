
#pragma once

#include <string>
#include <vector>

namespace Bounty
{
	namespace OpenGL
	{

		class VertexAttributes
		{
		public:
			struct  SVertexAttribute
			{
			public:
				SVertexAttribute(const std::string& szName, unsigned int shaderLocation, unsigned int numDataTypePerData, unsigned int stridesInBytes, unsigned int bufferOffsetInBytes, bool bIsInteger = false, unsigned int perInstanceDivisor = 0)
				{
					m_szName = szName;
					m_ShaderLocation = shaderLocation;
					m_NumDataTypePerData = numDataTypePerData;
					m_StridesInBytes = stridesInBytes;
					m_BufferOffsetInBytes = bufferOffsetInBytes;
					m_InstanceDivisor = perInstanceDivisor;
					m_bIsInteger = bIsInteger;
				}
				const SVertexAttribute& operator = (const SVertexAttribute& vertexAttribute)
				{
					m_szName = vertexAttribute.m_szName;
					m_ShaderLocation = vertexAttribute.m_ShaderLocation;
					m_NumDataTypePerData = vertexAttribute.m_NumDataTypePerData;
					m_StridesInBytes = vertexAttribute.m_StridesInBytes;
					m_BufferOffsetInBytes = vertexAttribute.m_BufferOffsetInBytes;
					m_InstanceDivisor = vertexAttribute.m_InstanceDivisor;
					m_bIsInteger = vertexAttribute.m_bIsInteger;
					return *this;
				}
				
#pragma warning ( push )
#pragma warning ( disable : 4251 ) 
				std::string m_szName;
#pragma warning ( pop )

				unsigned int m_ShaderLocation;
				unsigned int m_NumDataTypePerData;
				unsigned int m_StridesInBytes;
				unsigned int m_BufferOffsetInBytes;
				unsigned int m_InstanceDivisor;
				bool m_bIsInteger;
			};
		public:
			VertexAttributes();
			~VertexAttributes();
			virtual void clear();
			virtual void bind();
			virtual void unbind();
			virtual void addAttribute(const SVertexAttribute& vertexAttribute);
			virtual void addAttribute(const std::string& szName, unsigned int attribLoc, unsigned int numDataTypePerData, unsigned int stridesInBytes, unsigned int bufferOffsetInBytes, bool bIsInteger = false);
			virtual unsigned int getNumberOfAttributes();
			virtual const SVertexAttribute* getAttribute(unsigned int index);
		protected:
#pragma warning ( push )
#pragma warning ( disable : 4251 ) 
			std::vector<SVertexAttribute> m_vVertexAttributes;
#pragma warning ( pop )
		};

	}

}
