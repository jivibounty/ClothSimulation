
#ifndef Gravity_h
#define Gravity_h

#include "IExternalForceGenerator.h"
#include <glm/glm.hpp>

namespace Cloth
{
	
	class Gravity : public IExternalForceGenerator
	{
	public:
		Gravity();
		
		Gravity(const glm::vec3& acceleration);
		
		virtual ~Gravity();
			
		inline const glm::vec3& getAcceleration() const { return m_Acceleration; }
			
		void setAcceleration(const glm::vec3& acceleration);
		
		virtual void applyForce(SimulationObject& simulationObject);
		
	protected:
		
		glm::vec3 m_Acceleration;
	};
	
}

#endif //Gravity_h
