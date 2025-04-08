#pragma once

class CPythonExceptionSender : public IPythonExceptionSender
{
	public:
		CPythonExceptionSender();
		virtual ~CPythonExceptionSender();

		void Send();

	protected:
		std::set<DWORD> m_kSet_dwSendedExceptionCRC;
};
//martysama0134's a288e6779da68f768431f9975e780da3
