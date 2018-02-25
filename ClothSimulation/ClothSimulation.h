
#ifndef ClothSimulation_h
#define ClothSimulation_h

#include "SimulationObject.h"
#include "IExternalForceGenerator.h"
#include "IInternalForceGenerator.h"
#include "IIntegrator.h"
#include "IConstraint.h"
#include "Program.h"
#include "BufferObject.h"
#include "DrawElements.h"
#include "VertexAttributes.h"
#include <vector>

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

#include <GLFW\glfw3.h>
#pragma comment(lib, "glfw3.lib")    // Link libraries
#pragma comment(lib, "glfw3dll.lib")    // Link libraries

#define GRID_SIZE 15

namespace Cloth
{

	class ClothSimulation
	{
	public:
		ClothSimulation();

		virtual ~ClothSimulation();

		void update(double fElapsedTime);

		void render();
	protected:

		SimulationObject m_ppSimulationObjects[GRID_SIZE][GRID_SIZE];

		std::vector<IExternalForceGenerator*> m_vExternalForceGenerators;

		std::vector<IInternalForceGenerator*> m_vInternalForceGenerators;

		IIntegrator* m_pIntegrator;

		std::vector<IConstraint*> m_vConstraints;

		IConstraint* m_PointConstraints[4];

		bool m_bIsPointConstraintActive[4];

		unsigned int m_NumConstraintIterations;

		double m_fElapsedTimeAccumulator;

		Bounty::OpenGL::Program* m_pProgram;

		Bounty::OpenGL::BufferObject* m_pIbo;

		Bounty::OpenGL::BufferObject* m_pVbo;

		Bounty::OpenGL::VertexAttributes* m_pVertexAttributes;

		Bounty::OpenGL::DrawElements* m_pDrawElements;

		int m_MvpUniforms;

		GLFWwindow* m_pWindow;
	};

}

#endif //ClothSimulation_h

