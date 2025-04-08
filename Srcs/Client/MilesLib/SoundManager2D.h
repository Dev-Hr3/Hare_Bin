#ifndef __MILESLIB_CSOUNDMANAGER2D_H__
#define __MILESLIB_CSOUNDMANAGER2D_H__

#include "SoundBase.h"
#include "SoundInstance.h"

class CSoundManager2D : public CSoundBase
{
	public:
		enum
		{
			INSTANCE_MAX_COUNT = 4
		};

		CSoundManager2D();
		virtual ~CSoundManager2D();

		bool				Initialize();
		void				Destroy();

		ISoundInstance *	GetInstance(const char* filename);

	protected:
		CSoundInstance2D	ms_Instances[INSTANCE_MAX_COUNT];
};

#endif
//martysama0134's a288e6779da68f768431f9975e780da3
