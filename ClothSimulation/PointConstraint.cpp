
#include "PointConstraint.h"

namespace Cloth
{
	
	PointConstraint::PointConstraint(SimulationObject& simulationObject)
		: m_SimulationObject(simulationObject)
	{
		m_Point = m_SimulationObject.getCurrentPosition();
	}
		
	PointConstraint::PointConstraint(SimulationObject& simulationObject, const glm::vec3& point)
		: m_SimulationObject(simulationObject)
		, m_Point(point)
	{
	}
	
	PointConstraint::~PointConstraint()
	{
	}
	
	void PointConstraint::setPoint(const glm::vec3& point)
	{
		m_Point = point;
	}
	
	void PointConstraint::satisfyConstraint()
	{
		m_SimulationObject.setCurrentPosition(m_Point);
	}
	
}

