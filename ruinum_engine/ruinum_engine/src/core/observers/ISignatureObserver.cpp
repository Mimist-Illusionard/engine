#ifndef ISIGNATURE_OBSERVER
#define ISIGNATURE_OBSERVER

#include "../ECS.h"

class ISignatureObserver
{
public:
	virtual void SignatureChanged(Entity entity, Signature signature) {}
};

#endif