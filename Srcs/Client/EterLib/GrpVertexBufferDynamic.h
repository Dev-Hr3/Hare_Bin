#pragma once

#include "GrpVertexBuffer.h"

class CDynamicVertexBuffer : public CGraphicVertexBuffer
{
	public:
		CDynamicVertexBuffer();
		virtual ~CDynamicVertexBuffer();

		bool Create(int vtxCount, int fvf);

	protected:
		int m_vtxCount;
		int m_fvf;
};
//martysama0134's a288e6779da68f768431f9975e780da3
