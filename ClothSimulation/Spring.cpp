
#include "Spring.h"
#include <stdio.h>

namespace Cloth
{
	
	Spring::Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB)
		: m_SimulationObjectA(simulationObjectA)
		, m_SimulationObjectB(simulationObjectB)
		, m_fStiffness(2.0f)
		, m_fDamping(0.02f)
	{
		m_fRestLength = glm::length(m_SimulationObjectA.getCurrentPosition() - m_SimulationObjectB.getCurrentPosition());
	}
		
	Spring::Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fStiffness, float fDamping)
		: m_SimulationObjectA(simulationObjectA)
		, m_SimulationObjectB(simulationObjectB)
		, m_fStiffness(fStiffness)
		, m_fDamping(fDamping)
	{
		m_fRestLength = glm::length(m_SimulationObjectA.getCurrentPosition() - m_SimulationObjectB.getCurrentPosition());
	}
		
	Spring::Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fStiffness, float fDamping, float fRestLength)
		: m_SimulationObjectA(simulationObjectA)
		, m_SimulationObjectB(simulationObjectB)
		, m_fStiffness(fStiffness)
		, m_fDamping(fDamping)
		, m_fRestLength(fRestLength)
	{
	}
		
	Spring::~Spring()
	{
	}
		
	void Spring::setStiffness(float fStiffness)
	{
		m_fStiffness = fStiffness;
	}
	
	void Spring::setDamping(float fDamping)
	{
		m_fDamping = fDamping;
	}
	
	void Spring::setRestLength(float fRestLength)
	{
		m_fRestLength = fRestLength;
	}
	
	void Spring::applyForce()
	{
		//get the direction vector
		glm::vec3 direction = m_SimulationObjectA.getCurrentPosition() - m_SimulationObjectB.getCurrentPosition();
		//check for zero vector
		if (direction != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			//get length
			float currentLength = glm::length(direction);
			//normalize
			direction = glm::normalize(direction);
			//add spring force
			glm::vec3 force = -m_fStiffness * ((currentLength - m_fRestLength) * direction);
			//add spring damping force
			force += -m_fDamping * glm::dot(m_SimulationObjectA.getVelocity() - m_SimulationObjectB.getVelocity(), direction) * direction;
			//apply the equal and opposite forces to the objects
			m_SimulationObjectA.addForce(force);
			m_SimulationObjectB.addForce(-force);
		}
	}
	
}
