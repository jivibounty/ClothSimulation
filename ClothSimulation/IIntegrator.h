
#ifndef IIntegrator_h
#define IIntegrator_h

#include "SimulationObject.h"

namespace Cloth
{
	
	class IIntegrator
	{
	public:
		IIntegrator(double fFixedTimeStep)
			: m_fFixedTimeStep(fFixedTimeStep)
		{}
		
		virtual ~IIntegrator() {}
		
		inline double getFixedTimeStep() const { return m_fFixedTimeStep; }
		
		inline void setFixedTimeStep(float fFixedTimeStep) { m_fFixedTimeStep = fFixedTimeStep;	}
		
		virtual void integrate(SimulationObject& simulationObject) = 0;
	protected:
		
		double m_fFixedTimeStep;
	};
	
}

#endif //IIntegrator_h

