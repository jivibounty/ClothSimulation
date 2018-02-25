
#ifndef VerletNoVelocityIntegrator_h
#define VerletNoVelocityIntegrator_h

#include "IIntegrator.h"

namespace Cloth
{
	
	class VerletNoVelocityIntegrator : public IIntegrator
	{
	public:
		VerletNoVelocityIntegrator();
		
		VerletNoVelocityIntegrator(double fFixedTimeStep);
		
		virtual ~VerletNoVelocityIntegrator();
		
		inline float getDrag() const { return m_fDrag; }
		
		void setDrag(float fDrag);
		
		virtual void integrate(SimulationObject& simulationObject);
	protected:
		
		float m_fDrag;
	};
	
}

#endif //VerletNoVelocityIntegrator_h

