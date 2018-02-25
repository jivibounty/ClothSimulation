
#include "Gravity.h"

#define EARTH_ACCELERATION_DUE_TO_GRAVITY 9.8f

namespace Cloth
{
	
	Gravity::Gravity()
		: m_Acceleration(glm::vec3(0.0f, -EARTH_ACCELERATION_DUE_TO_GRAVITY, 0.0f))
	{
	}
	
	Gravity::Gravity(const glm::vec3& acceleration)
		: m_Acceleration(acceleration)
	{
	}
	
	Gravity::~Gravity()
	{
	}
			
	void Gravity::setAcceleration(const glm::vec3& acceleration)
	{
		m_Acceleration = acceleration;
	}
	
	void Gravity::applyForce(SimulationObject& simulationObject)
	{
		simulationObject.addForce(simulationObject.getMass() * m_Acceleration);
	}
	
}

