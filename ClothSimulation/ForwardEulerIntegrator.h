
#ifndef ForwardEulerIntegrator_h
#define ForwardEulerIntegrator_h

#include "IIntegrator.h"

namespace Cloth
{
	
	class ForwardEulerIntegrator : public IIntegrator
	{
	public:
		ForwardEulerIntegrator();
		
		ForwardEulerIntegrator(double fFixedTimeStep);
		
		virtual ~ForwardEulerIntegrator();
		
		virtual void integrate(SimulationObject& simulationObject);
	};
	
}

#endif //ForwardEulerIntegrator_h

