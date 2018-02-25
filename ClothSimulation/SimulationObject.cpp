
#include "SimulationObject.h"

#define DEFAULT_MASS 2.0f

namespace Cloth
{

	SimulationObject::SimulationObject()
		: m_fMass(DEFAULT_MASS)
		, m_bIsActive(true)
	{	
	}

	SimulationObject::SimulationObject(float fMass)
		: m_fMass(fMass)
	{
	}

	SimulationObject::~SimulationObject()
	{
	}
	
			
	void SimulationObject::setMass(float fMass)
	{
		m_fMass = fMass;
	}
			
	void SimulationObject::setCurrentPosition(const glm::vec3& currentPosition)
	{
		m_CurrentPosition = currentPosition;
	}
			
	void SimulationObject::setPreviousPosition(const glm::vec3& previousPosition)
	{
		m_PreviousPosition = previousPosition;
	}
			
	void SimulationObject::updatePreviousPosition()
	{
		m_PreviousPosition = m_CurrentPosition;
	}
			
	void SimulationObject::setVelocity(const glm::vec3& velocity)
	{
		m_Velocity = velocity;
	}
	
	void SimulationObject::setResultantForce(const glm::vec3& resultantForce)
	{
		m_ResultantForce = resultantForce;
	}
			
	void SimulationObject::addForce(const glm::vec3& force)
	{
		m_ResultantForce += force;
	}
	
	void SimulationObject::resetResultantForce()
	{
		m_ResultantForce = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	
	void SimulationObject::setActive(bool bIsActive)
	{
		m_bIsActive = bIsActive;
		if(!m_bIsActive)
		{
			m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	
}

