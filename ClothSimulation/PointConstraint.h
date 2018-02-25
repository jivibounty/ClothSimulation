
#ifndef PointConstraint_h
#define PointConstraint_h

#include "SimulationObject.h"
#include "IConstraint.h"
#include <glm\glm.hpp>

namespace Cloth
{
	
	class PointConstraint : public IConstraint
	{
	public:
		PointConstraint(SimulationObject& simulationObject);
		
		PointConstraint(SimulationObject& simulationObject, const glm::vec3& point);
		
		virtual ~PointConstraint();
		
		inline const glm::vec3& getPoint() const { return m_Point; }
		
		void setPoint(const glm::vec3& point);
		
		virtual void satisfyConstraint();
	protected:
		
		SimulationObject& m_SimulationObject;
		
		glm::vec3 m_Point;
	};
}

#endif //PointConstraint_h

