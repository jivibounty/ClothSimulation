
#include "VerletNoVelocityIntegrator.h"

namespace Cloth
{
	
	VerletNoVelocityIntegrator::VerletNoVelocityIntegrator()
		: IIntegrator(1.0f / 60.0f)
		, m_fDrag(0.005f)
	{
	}
		
	VerletNoVelocityIntegrator::VerletNoVelocityIntegrator(double fFixedTimeStep)
		: IIntegrator(fFixedTimeStep)
	{
	}
	
	VerletNoVelocityIntegrator::~VerletNoVelocityIntegrator()
	{
	}
	
	void VerletNoVelocityIntegrator::setDrag(float fDrag)
	{
		m_fDrag = fDrag;
	}
	
	void VerletNoVelocityIntegrator::integrate(SimulationObject& simulationObject)
	{
		if(!simulationObject.isActive())
		{
			return;
		}
		glm::vec3 acceleration;
		float fMass = simulationObject.getMass();
		if(fMass > 0.0f)
		{
			acceleration = simulationObject.getResultantForce() / fMass;
		}
		glm::vec3 newPosition = (2.0f - m_fDrag) * simulationObject.getCurrentPosition()
			- (1.0f - m_fDrag) * simulationObject.getPreviousPosition()
			+ acceleration * (float)m_fFixedTimeStep * (float)m_fFixedTimeStep;
		simulationObject.updatePreviousPosition();
		simulationObject.setCurrentPosition(newPosition);
	}
	
}

