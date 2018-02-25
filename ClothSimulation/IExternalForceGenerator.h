
#ifndef IForceGenerator_h
#define IForceGenerator_h

#include "SimulationObject.h"

namespace Cloth
{
	
	class IExternalForceGenerator
	{
	public:
		IExternalForceGenerator() {}
		
		virtual ~IExternalForceGenerator() {}
		
		virtual void applyForce(SimulationObject& simulationObject) = 0;
	};
	
}

#endif //IForceGenerator_h

