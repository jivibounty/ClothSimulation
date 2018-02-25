
#include "LengthConstraint.h"

namespace Cloth
{
	
	LengthConstraint::LengthConstraint(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB)
		: m_SimulationObjectA(simulationObjectA)
		, m_SimulationObjectB(simulationObjectB)
	{
		m_fLength = glm::length(m_SimulationObjectA.getCurrentPosition() - m_SimulationObjectB.getCurrentPosition());
	}
		
	LengthConstraint::LengthConstraint(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fLength)
		: m_SimulationObjectA(simulationObjectA)
		, m_SimulationObjectB(simulationObjectB)
		, m_fLength(fLength)
	{
	}
	
	LengthConstraint::~LengthConstraint()
	{
	}
	
	void LengthConstraint::setLength(float fLength)
	{
		m_fLength = fLength;
	}
	
	void LengthConstraint::satisfyConstraint()
	{
		//calculate direction
		glm::vec3 direction = m_SimulationObjectB.getCurrentPosition() - m_SimulationObjectA.getCurrentPosition();
		//calculate current length
		float currentLength = glm::length(direction);
		//check for zero vector
		if (direction != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			//normalize direction vector
			direction = glm::normalize(direction);
			//move to goal positions
			glm::vec3 moveVector = 0.5f * (currentLength - m_fLength) * direction;
			m_SimulationObjectA.setCurrentPosition(m_SimulationObjectA.getCurrentPosition() + moveVector);
			m_SimulationObjectB.setCurrentPosition(m_SimulationObjectB.getCurrentPosition() - moveVector);
		}
	}
	
}

