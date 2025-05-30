#pragma once

#include <map>

class CNetworkPacketHeaderMap
{
	public:
		typedef struct SPacketType
		{
			SPacketType(int iSize = 0, bool bFlag = false)
			{
				iPacketSize = iSize;
				isDynamicSizePacket = bFlag;
			}

			int iPacketSize;
			bool isDynamicSizePacket;
		} TPacketType;

	public:
		CNetworkPacketHeaderMap();
		virtual ~CNetworkPacketHeaderMap();

		void Set(int header, const TPacketType & rPacketType);
		bool Get(int header, TPacketType * pPacketType);

	protected:
		std::map<int, TPacketType> m_headerMap;
};
//martysama0134's a288e6779da68f768431f9975e780da3
