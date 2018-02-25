
#ifndef IInternalForceGenerator_h
#define IInternalForceGenerator_h

namespace Cloth
{
	
	class IInternalForceGenerator
	{
	public:
		IInternalForceGenerator() {}
		
		virtual ~IInternalForceGenerator() {}
		
		virtual void applyForce() = 0;
	};
	
}

#endif //IInternalForceGenerator_h

