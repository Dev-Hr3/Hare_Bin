#pragma once

class IFlyEventHandler
{
public:
	IFlyEventHandler() {}
	virtual ~IFlyEventHandler() {}

	// Call by ActorInstance
	virtual void OnSetFlyTarget() {}
	virtual void OnShoot(DWORD dwSkillIndex) {}

	virtual void OnNoTarget() {}
	virtual void OnNoArrow() {}

	// Call by FlyingInstance
	virtual void OnExplodingOutOfRange() {}
	virtual void OnExplodingAtBackground() {}
	virtual void OnExplodingAtAnotherTarget(DWORD dwSkillIndex, DWORD dwVID) {}
	virtual void OnExplodingAtTarget(DWORD dwSkillIndex) {}
};
//martysama0134's a288e6779da68f768431f9975e780da3
