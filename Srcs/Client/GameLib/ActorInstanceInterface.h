#pragma once

#include "../eterGrnLib/ThingInstance.h"

class IActorInstance : public CGraphicThingInstance
{
public:
	enum
	{
		ID = ACTOR_OBJECT
	};
	int GetType() const { return ID; }

	IActorInstance() {}
	virtual ~IActorInstance() {}
	virtual bool TestCollisionWithDynamicSphere(const CDynamicSphereInstance & dsi) = 0;
	virtual DWORD GetVirtualID() = 0;
};
//martysama0134's a288e6779da68f768431f9975e780da3
