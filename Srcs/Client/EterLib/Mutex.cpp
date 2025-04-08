#include "StdAfx.h"
#include "Mutex.h"

Mutex::Mutex()
{
	InitializeCriticalSection(&lock);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&lock);
}

void Mutex::Lock()
{
	EnterCriticalSection(&lock);
}

void Mutex::Unlock()
{
	LeaveCriticalSection(&lock);
}
//martysama0134's a288e6779da68f768431f9975e780da3
