#pragma once

#include "MSWindow.h"

class CMSApplication : public CMSWindow
{
	public:
		CMSApplication();
		virtual ~CMSApplication();

		void Initialize(HINSTANCE hInstance);

		void MessageLoop();

		bool IsMessage();
		bool MessageProcess();

	protected:
		void ClearWindowClass();

		LRESULT WindowProcedure(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
};
//martysama0134's a288e6779da68f768431f9975e780da3
