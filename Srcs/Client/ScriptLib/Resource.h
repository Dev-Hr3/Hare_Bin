#pragma once

#include "../EffectLib/StdAfx.h"
#include "../eterlib/Resource.h"
#include "../eterlib/ResourceManager.h"

enum EResourceTypes
{
	RES_TYPE_UNKNOWN,
};

class CPythonResource : public CSingleton<CPythonResource>
{
	public:
		CPythonResource();
		virtual ~CPythonResource();

		void Destroy();

		void DumpFileList(const char * c_szFileName);

	protected:
		CResourceManager m_resManager;
};
//martysama0134's a288e6779da68f768431f9975e780da3
