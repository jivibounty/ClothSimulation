
#ifndef IConstraint_h
#define IConstraint_h

namespace  Cloth
{
	
	class IConstraint
	{
	public:
		IConstraint() {}
		
		virtual ~IConstraint() {}
		
		virtual void satisfyConstraint() = 0;
	};
}

#endif //IConstraint_h

