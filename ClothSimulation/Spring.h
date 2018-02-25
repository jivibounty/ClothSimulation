
#ifndef Spring_h
#define Spring_h

#include "IInternalForceGenerator.h"
#include "SimulationObject.h"

namespace Cloth
{
	
	class Spring : public IInternalForceGenerator
	{
	public:
		Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB);
		
		Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fStiffness, float fDamping);
		
		Spring(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fStiffness, float fDamping, float fRestLength);
		
		virtual ~Spring();
		
		inline float getStiffness() const { return m_fStiffness; }
		
		void setStiffness(float fStiffness);
		
		inline float getDamping() const { return m_fDamping; }
		
		void setDamping(float fDamping);
		
		inline float getRestLength() const { return m_fRestLength; }
		
		void setRestLength(float fRestLength);
		
		virtual void applyForce();
	protected:
		
		SimulationObject& m_SimulationObjectA;
		
		SimulationObject& m_SimulationObjectB;
		
		float m_fStiffness;
		
		float m_fDamping;
		
		float m_fRestLength;
	};
	
}

#endif //Spring_h

