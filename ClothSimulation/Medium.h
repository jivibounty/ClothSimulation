
#ifndef Medium_h
#define Medium_h

#include "IExternalForceGenerator.h"

namespace Cloth
{
	
	class Medium : public IExternalForceGenerator
	{
	public:
		Medium();
		
		Medium(float fDragCoefficient);
		
		virtual ~Medium();
		
		inline float getDragCoefficient() const { return m_fDragCoefficient; }
		
		void setDragCoeffiecient(float fDragCoefficient);
		
		virtual void applyForce(SimulationObject& simulationObject);
	protected:
		
		float m_fDragCoefficient;
	};
	
}

#endif //Medium_h

