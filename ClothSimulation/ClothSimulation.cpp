
#include "ClothSimulation.h"
#include "Gravity.h"
#include "Medium.h"
#include "Spring.h"
#include "ForwardEulerIntegrator.h"
#include "VerletNoVelocityIntegrator.h"
#include "LengthConstraint.h"
#include "PointConstraint.h"
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#define NATURAL_LENGTH 0.1f
#define NUM_CONSTRAINT_ITERATIONS 5
#define STRUCTURAL_STIFFNESS 2.0f
#define STRUCTURAL_DAMPING 0.02f
#define SHEAR_STIFFNESS 2.0f
#define SHEAR_DAMPING 0.02f
#define BEND_STIFFNESS 2.0f
#define BEND_DAMPING 0.02f
#define AIR_DRAG_COEFFICIENT 0.5f
#define MAX_ELAPSED_TIME 2.0
#define PI 3.1415926535897932384626433832795028841971693993751f
#define PI_RAD 0.01745329251994329576923690768489f

namespace Cloth
{

	ClothSimulation::ClothSimulation()
		: m_NumConstraintIterations(NUM_CONSTRAINT_ITERATIONS)
		, m_fElapsedTimeAccumulator(0.0)
		, m_MvpUniforms(-1)
	{
		m_pIntegrator = new VerletNoVelocityIntegrator;
		float offsetX = NATURAL_LENGTH * -(float)GRID_SIZE / 2.0;
		float offsetZ = NATURAL_LENGTH * -(float)GRID_SIZE / 2.0;
		for(unsigned int x = 0; x < GRID_SIZE; ++x)
		{
			for(unsigned int z = 0; z < GRID_SIZE; ++z)
			{
				m_ppSimulationObjects[x][z].setCurrentPosition(glm::vec3(offsetX + NATURAL_LENGTH * x, 0.0f, offsetZ + NATURAL_LENGTH * z));
				m_ppSimulationObjects[x][z].setPreviousPosition(m_ppSimulationObjects[x][z].getCurrentPosition());
			}
		}
		m_vExternalForceGenerators.push_back(new Gravity);
		//m_vExternalForceGenerators.push_back(new Medium(AIR_DRAG_COEFFICIENT));
		for (int x = 0; x < (GRID_SIZE - 1); ++x)
		{
			for (int z = 0; z < GRID_SIZE; ++z)
			{
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 1][z], STRUCTURAL_STIFFNESS, STRUCTURAL_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 1][z]));
			}
		}
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int z = 0; z < (GRID_SIZE - 1); ++z)
			{
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x][z + 1], STRUCTURAL_STIFFNESS, STRUCTURAL_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x][z + 1]));
			}
		}
		for (int x = 0; x < (GRID_SIZE - 1); ++x)
		{
			for (int z = 0; z < (GRID_SIZE - 1); ++z)
			{
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x + 1][z], m_ppSimulationObjects[x][z + 1], SHEAR_STIFFNESS, SHEAR_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x + 1][z], m_ppSimulationObjects[x][z + 1]));
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 1][z + 1], SHEAR_STIFFNESS, SHEAR_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 1][z + 1]));
			}
		}
		for (int x = 0; x < (GRID_SIZE - 2); ++x)
		{
			for (int z = 0; z < GRID_SIZE; ++z)
			{
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 2][z], BEND_STIFFNESS, BEND_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x + 2][z]));
			}
		}
		for (int x = 0; x < GRID_SIZE; ++x)
		{
			for (int z = 0; z < (GRID_SIZE - 2); ++z)
			{
				m_vInternalForceGenerators.push_back(new Spring(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x][z + 2], BEND_STIFFNESS, BEND_DAMPING));
				m_vConstraints.push_back(new LengthConstraint(m_ppSimulationObjects[x][z], m_ppSimulationObjects[x][z + 2]));
			}
		}
		m_ppSimulationObjects[0][0].setActive(false);
		m_PointConstraints[0] = new PointConstraint(m_ppSimulationObjects[0][0]);
		m_bIsPointConstraintActive[0] = true;
		m_ppSimulationObjects[0][GRID_SIZE - 1].setActive(false);
		m_PointConstraints[1] = new PointConstraint(m_ppSimulationObjects[0][GRID_SIZE - 1]);
		m_bIsPointConstraintActive[1] = true;
		m_ppSimulationObjects[GRID_SIZE - 1][0].setActive(false);
		m_PointConstraints[2] = new PointConstraint(m_ppSimulationObjects[GRID_SIZE - 1][0]);
		m_bIsPointConstraintActive[2] = true;
		m_ppSimulationObjects[GRID_SIZE - 1][GRID_SIZE - 1].setActive(false);
		m_PointConstraints[3] = new PointConstraint(m_ppSimulationObjects[GRID_SIZE - 1][GRID_SIZE - 1]);
		m_bIsPointConstraintActive[3] = true;
		// Initialize GLFW
		if (!glfwInit())
		{
			printf("Glfw did not initialize\n");
		}

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		// Create Window
		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		m_pWindow = glfwCreateWindow(800, 600, "Cloth Simulation", NULL, NULL);
		if(m_pWindow == NULL)
		{
			glfwTerminate();
		}

		// Make an OpenGL context in the given window
		glfwMakeContextCurrent(m_pWindow);

		if (glewInit() != GLEW_OK)
		{
			printf("Glew did not initialize\n");
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glDepthFunc(GL_LEQUAL);

		m_pProgram = new Bounty::OpenGL::Program;
		Bounty::OpenGL::Shader vertexShader;
		vertexShader.loadShaderFromFile("vertex.glsl", GL_VERTEX_SHADER);
		Bounty::OpenGL::Shader fragmentShader;
		fragmentShader.loadShaderFromFile("fragment.glsl", GL_FRAGMENT_SHADER);
		m_pProgram->addShader(vertexShader);
		m_pProgram->addShader(fragmentShader);
		m_pVbo = new Bounty::OpenGL::BufferObject;
		glm::vec3 pVertices[GRID_SIZE * GRID_SIZE];
		unsigned int vertexOffset = 0;
		for(unsigned int x = 0; x < GRID_SIZE; ++x)
		{
			for(unsigned int z = 0; z < GRID_SIZE; ++z)
			{
				pVertices[vertexOffset++] = m_ppSimulationObjects[x][z].getCurrentPosition();
			}
		}
		m_pVbo->create(GL_ARRAY_BUFFER, pVertices, GRID_SIZE * GRID_SIZE, sizeof(glm::vec3), GL_STREAM_DRAW);
		m_pIbo = new Bounty::OpenGL::BufferObject;
		unsigned int pIndices[(GRID_SIZE - 1) * (GRID_SIZE - 1) * 3 * 2];
		unsigned int indexOffset = 0;
		for(unsigned int x = 0; x < (GRID_SIZE - 1); ++x)
		{
			for(unsigned int z = 0; z < (GRID_SIZE - 1); ++z)
			{
				pIndices[indexOffset++] = x + z * GRID_SIZE;
				pIndices[indexOffset++] = x + 1 + (z + 1) * GRID_SIZE;
				pIndices[indexOffset++] = x + (z + 1) * GRID_SIZE;
				pIndices[indexOffset++] = x + z * GRID_SIZE;
				pIndices[indexOffset++] = x + 1 + z * GRID_SIZE;
				pIndices[indexOffset++] = x + 1 + (z + 1) * GRID_SIZE;
			}
		}
		m_pIbo->create(GL_ELEMENT_ARRAY_BUFFER, pIndices, (GRID_SIZE - 1) * (GRID_SIZE - 1) * 3 * 2, sizeof(unsigned int), GL_STATIC_DRAW);
		m_pVertexAttributes = new Bounty::OpenGL::VertexAttributes;
		m_pVertexAttributes->addAttribute("Position", 0, 3, sizeof(glm::vec3), 0);
		m_pDrawElements = new Bounty::OpenGL::DrawElements;
		m_pDrawElements->setInstanceCount(1);
		m_pDrawElements->setIndexOffset(0);
		m_pDrawElements->setIndexCount(indexOffset);
		m_pDrawElements->setDrawMode(GL_TRIANGLES);
	}

	ClothSimulation::~ClothSimulation()
	{
		for(unsigned int n = 0; n < m_vExternalForceGenerators.size(); ++n)
		{
			if(m_vExternalForceGenerators[n])
			{
				delete m_vExternalForceGenerators[n];
				m_vExternalForceGenerators[n] = nullptr;
			}
		}
		m_vExternalForceGenerators.clear();
		for(unsigned int n = 0; n < m_vInternalForceGenerators.size(); ++n)
		{
			if(m_vInternalForceGenerators[n])
			{
				delete m_vInternalForceGenerators[n];
				m_vInternalForceGenerators[n] = nullptr;
			}
		}
		m_vInternalForceGenerators.clear();
		if(m_pIntegrator)
		{
			delete m_pIntegrator;
			m_pIntegrator = nullptr;
		}
		for(unsigned int n = 0; n < m_vConstraints.size(); ++n)
		{
			if(m_vConstraints[n])
			{
				delete m_vConstraints[n];
				m_vConstraints[n] = nullptr;
			}
		}
		m_vConstraints.clear();
	}

	void ClothSimulation::update(double fElapsedTime)
	{
		if(fElapsedTime > MAX_ELAPSED_TIME)
		{
			fElapsedTime = MAX_ELAPSED_TIME;
		}
		double fFixedTimeStep = 1.0 / 60.0;
		if(m_pIntegrator)
		{
			fFixedTimeStep = m_pIntegrator->getFixedTimeStep();
		}
		m_fElapsedTimeAccumulator += fElapsedTime;
		while(m_fElapsedTimeAccumulator >= fFixedTimeStep)
		{
			m_fElapsedTimeAccumulator -= fFixedTimeStep;
			for(unsigned int n = 0; n < m_vExternalForceGenerators.size(); ++n)
			{
				if(m_vExternalForceGenerators[n])
				{
					for(unsigned int x = 0; x < GRID_SIZE; ++x)
					{
						for(unsigned int z = 0; z < GRID_SIZE; ++z)
						{
							m_vExternalForceGenerators[n]->applyForce(m_ppSimulationObjects[x][z]);
						}
					}
				}
			}
			for(unsigned int n = 0; n < m_vInternalForceGenerators.size(); ++n)
			{
				if(m_vInternalForceGenerators[n])
				{
					m_vInternalForceGenerators[n]->applyForce();	
				}
			}
			if(m_pIntegrator)
			{
				for(unsigned int x = 0; x < GRID_SIZE; ++x)
				{
					for(unsigned int z = 0; z < GRID_SIZE; ++z)
					{
						m_pIntegrator->integrate(m_ppSimulationObjects[x][z]);
						m_ppSimulationObjects[x][z].resetResultantForce();
					}
				}
			}
			for(unsigned int i = 0; i < m_NumConstraintIterations; ++i)
			{
				for(unsigned int n = 0; n < 4; ++n)
				{
					if(m_bIsPointConstraintActive[n] && m_PointConstraints[n] != nullptr)
					{
						m_PointConstraints[n]->satisfyConstraint();
					}
				}
				for(unsigned int n = 0; n < m_vConstraints.size(); ++n)
				{
					if(m_vConstraints[n])
					{
						m_vConstraints[n]->satisfyConstraint();
					}
				}
			}
		}	
	}

	void ClothSimulation::render()
	{
		if(!m_pWindow)
		{
			return;
		}
		glfwPollEvents();
		if(glfwGetKey(m_pWindow, 'Q') == GLFW_PRESS)
		{
			m_ppSimulationObjects[0][0].setActive(true);
			m_bIsPointConstraintActive[0] = false;
		}
		if(glfwGetKey(m_pWindow, 'W') == GLFW_PRESS)
		{
			m_ppSimulationObjects[0][GRID_SIZE - 1].setActive(true);
			m_bIsPointConstraintActive[1] = false;
		}
		if(glfwGetKey(m_pWindow, 'E') == GLFW_PRESS)
		{
			m_ppSimulationObjects[GRID_SIZE - 1][0].setActive(true);
			m_bIsPointConstraintActive[2] = false;
		}
		if(glfwGetKey(m_pWindow, 'R') == GLFW_PRESS)
		{
			m_ppSimulationObjects[GRID_SIZE - 1][GRID_SIZE - 1].setActive(true);
			m_bIsPointConstraintActive[3] = false;
		}

		if(!m_pProgram || !m_pIbo || !m_pVbo || !m_pVertexAttributes || !m_pDrawElements)
		{
			return;
		}
		//render
		int width = 800;
		int height = 600;
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		m_pProgram->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if(m_MvpUniforms < 0)
		{
			m_MvpUniforms = m_pProgram->getParameter("gMVP");
		}
		glm::mat4 glmMvp = glm::perspective(60.0f * PI_RAD, 16.0f / 9.0f, 0.1f, 5000.0f)
			* glm::lookAt(glm::vec3(1.2f, 1.2f, 1.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(m_MvpUniforms, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(glmMvp));

		m_pIbo->bind();
		glm::vec3 pVertices[GRID_SIZE * GRID_SIZE];
		unsigned int vertexOffset = 0;
		for(unsigned int x = 0; x < GRID_SIZE; ++x)
		{
			for(unsigned int z = 0; z < GRID_SIZE; ++z)
			{
				pVertices[vertexOffset++] = m_ppSimulationObjects[x][z].getCurrentPosition();
			}
		}
		m_pVbo->update(pVertices, 0, GRID_SIZE * GRID_SIZE, sizeof(glm::vec3));
		m_pVbo->bind();
		m_pVertexAttributes->bind();
		if(m_pProgram->isValidated())
		{
			m_pDrawElements->draw();
		}
		m_pVertexAttributes->unbind();
		m_pVbo->unbind();
		m_pIbo->unbind();
		m_pProgram->unbind();

		glfwSwapBuffers(m_pWindow);
	}

}

