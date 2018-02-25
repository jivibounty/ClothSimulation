
#ifndef SimulationObject_h
#define SimulationObject_h

#include <glm\glm.hpp>

namespace Cloth
{
	
	class SimulationObject
	{
	public:
		SimulationObject();
			
		SimulationObject(float fMass);
			
		virtual ~SimulationObject();
			
		inline float getMass() const { return m_fMass; }
			
		void setMass(float fMass);
			
		inline const glm::vec3& getCurrentPosition() const { return m_CurrentPosition; }
			
		void setCurrentPosition(const glm::vec3& currentPosition);
			
		inline const glm::vec3& getPreviousPosition() const { return m_PreviousPosition; }
			
		void setPreviousPosition(const glm::vec3& previousPosition);

		void updatePreviousPosition();
			
		inline const glm::vec3& getVelocity() const { return m_Velocity; }
			
		void setVelocity(const glm::vec3& velocity);
			
		inline const glm::vec3& getResultantForce() const { return m_ResultantForce; }
			
		void setResultantForce(const glm::vec3& resultantForce);
			
		void addForce(const glm::vec3& force);
			
		void resetResultantForce();

		inline bool isActive() const { return m_bIsActive; }

		void setActive(bool bIsActive);
	protected:
			
		float m_fMass;
			
		glm::vec3 m_CurrentPosition;
			
		glm::vec3 m_PreviousPosition;
			
		glm::vec3 m_Velocity;
		
		glm::vec3 m_ResultantForce;
		
		bool m_bIsActive;
	};
	
}

#endif //SimulationObject_h

