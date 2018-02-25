
#include "Medium.h"

namespace Cloth
{
	
	Medium::Medium()
		: m_fDragCoefficient(1.0f)
	{
	}
	
	Medium::Medium(float fDragCoefficient)
		: m_fDragCoefficient(fDragCoefficient)
	{
	}
	
	Medium::~Medium()
	{
	}
		
	void Medium::setDragCoeffiecient(float fDragCoefficient)
	{
		m_fDragCoefficient = fDragCoefficient;
	}
		
	void Medium::applyForce(SimulationObject& simulationObject)
	{
		simulationObject.addForce(simulationObject.getVelocity() * -m_fDragCoefficient);
	}
	
}

