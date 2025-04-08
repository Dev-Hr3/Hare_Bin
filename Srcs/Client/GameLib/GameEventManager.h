#pragma once

#include "ActorInstance.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	CGameEventManager
//
//
//

class CGameEventManager : public CSingleton<CGameEventManager>, public CScreen
{
	public:
		CGameEventManager();
		virtual ~CGameEventManager();

		void SetCenterPosition(float fx, float fy, float fz);
		void Update();

		void ProcessEventScreenWaving(CActorInstance * pActorInstance, const CRaceMotionData::TScreenWavingEventData * c_pData);

	protected:
		TPixelPosition m_CenterPosition;
};
//martysama0134's a288e6779da68f768431f9975e780da3
