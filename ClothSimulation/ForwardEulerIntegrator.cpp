
#include "ForwardEulerIntegrator.h"

namespace Cloth
{
	
	ForwardEulerIntegrator::ForwardEulerIntegrator()
		: IIntegrator(1.0f / 60.0f)
	{
	}
		
	ForwardEulerIntegrator::ForwardEulerIntegrator(double fFixedTimeStep)
		: IIntegrator(fFixedTimeStep)
	{
	}
	
	ForwardEulerIntegrator::~ForwardEulerIntegrator()
	{
	}
	
	void ForwardEulerIntegrator::integrate(SimulationObject& simulationObject)
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
		//calculate new position using the velocity at current time
		simulationObject.setCurrentPosition(simulationObject.getCurrentPosition() + simulationObject.getVelocity() * (float)m_fFixedTimeStep);
		//calculate new velocity using the acceleration at current time
		simulationObject.setVelocity(simulationObject.getVelocity() + acceleration * (float)m_fFixedTimeStep);
	}
	
}

