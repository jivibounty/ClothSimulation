
#ifndef LengthConstraint_h
#define LengthConstraint_h

#include "SimulationObject.h"
#include "IConstraint.h"

namespace Cloth
{
	
	class LengthConstraint : public IConstraint
	{
	public:
		LengthConstraint(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB);
		
		LengthConstraint(SimulationObject& simulationObjectA, SimulationObject& simulationObjectB, float fLength);
		
		virtual ~LengthConstraint();
		
		inline float getLength() const { return m_fLength; }
		
		void setLength(float fLength);
		
		virtual void satisfyConstraint();
	protected:
		
		SimulationObject& m_SimulationObjectA;
		
		SimulationObject& m_SimulationObjectB;
		
		float m_fLength;
	};
}

#endif //LengthConstraint_h

