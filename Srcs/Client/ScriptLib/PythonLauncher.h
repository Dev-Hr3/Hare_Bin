#pragma once
#include <Python27/frameobject.h>

#include "../eterBase/Singleton.h"

class CPythonLauncher : public CSingleton<CPythonLauncher>
{
	public:
		CPythonLauncher();
		virtual ~CPythonLauncher();

		void Clear();

		bool Create(const char* c_szProgramName="eter.python");
		void SetTraceFunc(int (*pFunc)(PyObject * obj, PyFrameObject * f, int what, PyObject *arg));
		bool RunLine(const char* c_szLine);
		bool RunFile(const char* c_szFileName);
		bool RunMemoryTextFile(const char* c_szFileName, UINT uFileSize, const VOID* c_pvFileData);
		bool RunCompiledFile(const char* c_szFileName);
		const char* GetError();

	protected:
		PyObject* m_poModule;
		PyObject* m_poDic;
};
//martysama0134's a288e6779da68f768431f9975e780da3
