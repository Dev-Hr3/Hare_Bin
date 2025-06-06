#include <stdlib.h>
#include <lzo/lzoLibLink.h>

#include "lzo.h"
#include "tea.h"

#define dbg_printf printf
#define TraceError(...) fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");

static class LZOFreeMemoryMgr
{
public:
	enum
	{
		REUSING_CAPACITY = 64*1024,
	};
public:
	~LZOFreeMemoryMgr()
	{
		std::vector<BYTE*>::iterator i;
		for (i = m_freeVector.begin(); i != m_freeVector.end(); ++i)
			delete *i;

		m_freeVector.clear();
	}
	BYTE* Alloc(unsigned capacity)
	{
		assert(capacity > 0);
		if (capacity < REUSING_CAPACITY)
		{
			if (!m_freeVector.empty())
			{
				BYTE* freeMem = m_freeVector.back();
				m_freeVector.pop_back();

				dbg_printf("lzo.reuse_alloc\t%p(%d) free\n", freeMem, capacity);
				return freeMem;
			}
			auto newMem = new BYTE[REUSING_CAPACITY];
			dbg_printf("lzo.reuse_alloc\t%p(%d) real\n", newMem, capacity);
			return newMem;
		}
		auto newMem = new BYTE[capacity];
		dbg_printf("lzo.real_alloc\t%p(%d)\n", newMem, capacity);
		return newMem;
	}
	void Free(BYTE* ptr, unsigned capacity)
	{
		assert(ptr != nullptr);
		assert(capacity > 0);
		if (capacity < REUSING_CAPACITY)
		{
			dbg_printf("lzo.reuse_free\t%p(%d)\n", ptr, capacity);
			m_freeVector.push_back(ptr);
			return;
		}

		dbg_printf("lzo.real_free\t%p(%d)\n", ptr, capacity);
		delete [] ptr;
	}
private:
	std::vector<BYTE*> m_freeVector;
} gs_freeMemMgr;

DWORD CLZObject::ms_dwFourCC = MAKEFOURCC('M', 'C', 'O', 'Z');

CLZObject::CLZObject()
{
    Initialize();
}

void CLZObject::Initialize()
{
	m_bInBuffer = false;
    m_pbBuffer = nullptr;
    m_dwBufferSize = 0;

    m_pHeader = nullptr;
    m_pbIn = nullptr;
    m_bCompressed = false;
}

void CLZObject::Clear()
{
    if (m_pbBuffer && !m_bInBuffer)
		gs_freeMemMgr.Free(m_pbBuffer, m_dwBufferSize);

	if (m_dwBufferSize > 0)
	{
		dbg_printf("lzo.free %d\n", m_dwBufferSize);
	}

    Initialize();
}

CLZObject::~CLZObject()
{
    Clear();
}

DWORD CLZObject::GetSize() const
{
	assert(m_pHeader);

	if (m_bCompressed)
	{
		if (m_pHeader->dwEncryptSize)
			return sizeof(THeader) + sizeof(DWORD) + m_pHeader->dwEncryptSize;
		else
			return sizeof(THeader) + sizeof(DWORD) + m_pHeader->dwCompressedSize;
	}
	else
		return m_pHeader->dwRealSize;
}

void CLZObject::BeginCompress(const void * pvIn, UINT uiInLen)
{
    m_pbIn = (const BYTE *) pvIn;

    m_dwBufferSize = sizeof(THeader) + sizeof(DWORD) + (uiInLen + uiInLen / 64 + 16 + 3) + 8;

    m_pbBuffer = gs_freeMemMgr.Alloc(m_dwBufferSize);
    memset(m_pbBuffer, 0, m_dwBufferSize);

    m_pHeader = (THeader *) m_pbBuffer;
    m_pHeader->dwFourCC = ms_dwFourCC;
    m_pHeader->dwEncryptSize = m_pHeader->dwCompressedSize = m_pHeader->dwRealSize = 0;
    m_pHeader->dwRealSize = uiInLen;
}

void CLZObject::BeginCompressInBuffer(const void * pvIn, UINT uiInLen, void *)
{
    m_pbIn = (const BYTE *) pvIn;

    m_dwBufferSize = sizeof(THeader) + sizeof(DWORD) + (uiInLen + uiInLen / 64 + 16 + 3) + 8;

    m_pbBuffer = gs_freeMemMgr.Alloc(m_dwBufferSize);
    memset(m_pbBuffer, 0, m_dwBufferSize);

    m_pHeader = (THeader *) m_pbBuffer;
    m_pHeader->dwFourCC = ms_dwFourCC;
    m_pHeader->dwEncryptSize = m_pHeader->dwCompressedSize = m_pHeader->dwRealSize = 0;
    m_pHeader->dwRealSize = uiInLen;
	m_bInBuffer = true;
}

bool CLZObject::Compress()
{
    UINT	iOutLen;
    BYTE *	pbBuffer;

    pbBuffer = m_pbBuffer + sizeof(THeader);
    *(DWORD *) pbBuffer = ms_dwFourCC;
    pbBuffer += sizeof(DWORD);

#if defined( LZO1X_999_MEM_COMPRESS )
    int r = lzo1x_999_compress((BYTE *) m_pbIn, m_pHeader->dwRealSize, pbBuffer, (lzo_uint*) &iOutLen, CLZO::Instance().GetWorkMemory());
#else
    int r = lzo1x_1_compress((BYTE *) m_pbIn, m_pHeader->dwRealSize, pbBuffer, (lzo_uint*) &iOutLen, CLZO::Instance().GetWorkMemory());
#endif

    if (LZO_E_OK != r)
    {
		TraceError("LZO: lzo1x_999_compress failed");
		return false;
    }

    m_pHeader->dwCompressedSize = iOutLen;
    m_bCompressed = true;
    return true;
}

bool CLZObject::BeginDecompress(const void * pvIn)
{
	if (!pvIn) // @fixme044
	{
		TraceError("LZObject: pvIn is nullptr");
		return false;
	}

	const auto pHeader = (THeader *) pvIn;

    if (pHeader->dwFourCC != ms_dwFourCC)
    {
		TraceError("LZObject: not a valid data");
		return false;
    }

    m_pHeader	= pHeader;
    m_pbIn	= (const BYTE *) pvIn + (sizeof(THeader) + sizeof(DWORD));

	m_dwBufferSize = pHeader->dwRealSize;
	m_pbBuffer = gs_freeMemMgr.Alloc(m_dwBufferSize);
    memset(m_pbBuffer, 0, pHeader->dwRealSize);
    return true;
}

class DecryptBuffer
{
public:
	enum
	{
		LOCAL_BUF_SIZE = 8 * 1024,
	};
public:
	DecryptBuffer(unsigned size)
	{
		static unsigned count = 0;
		static unsigned sum = 0;
		static unsigned maxSize = 0;

		sum += size;
		count++;

		maxSize = (std::max)(size, maxSize);
		if (size >= LOCAL_BUF_SIZE)
		{
			m_buf = new char[size];
			dbg_printf("DecryptBuffer - AllocHeap %d max(%d) ave(%d)\n", size, maxSize/1024, sum/count);
		}
		else
		{
			dbg_printf("DecryptBuffer - AllocStack %d max(%d) ave(%d)\n", size, maxSize/1024, sum/count);
			m_buf = m_local_buf;
		}
	}
	~DecryptBuffer()
	{
		if (m_local_buf != m_buf)
		{
			dbg_printf("DecruptBuffer - FreeHeap\n");
			delete [] m_buf;
		}
		else
		{
			dbg_printf("DecruptBuffer - FreeStack\n");
		}
	}
	void* GetBufferPtr() const
	{
		return m_buf;
	}

private:
	char*	m_buf;
	char	m_local_buf[LOCAL_BUF_SIZE];
};

bool CLZObject::Decompress(DWORD * pdwKey) const
{
    UINT uiSize;
    int r;

    if (m_pHeader->dwEncryptSize)
    {
	    const DecryptBuffer buf(m_pHeader->dwEncryptSize);

		const auto pbDecryptedBuffer = (BYTE*)buf.GetBufferPtr();

		__Decrypt(pdwKey, pbDecryptedBuffer);

		if (*(DWORD *) pbDecryptedBuffer != ms_dwFourCC)
		{
			TraceError("LZObject: key incorrect");
			return false;
		}

		if (LZO_E_OK != (r = lzo1x_decompress(pbDecryptedBuffer + sizeof(DWORD), m_pHeader->dwCompressedSize, m_pbBuffer, (lzo_uint*) &uiSize, nullptr)))
		{
			TraceError("LZObject: Decompress failed(decrypt) ret %d\n", r);
			return false;
		}
    }
    else
    {
		uiSize = m_pHeader->dwRealSize;

		if (LZO_E_OK != (r = lzo1x_decompress(m_pbIn, m_pHeader->dwCompressedSize, m_pbBuffer, (lzo_uint*) &uiSize, nullptr)))
		{
			TraceError("LZObject: Decompress failed : ret %d, CompressedSize %d\n", r, m_pHeader->dwCompressedSize);
			return false;
		}
    }

    if (uiSize != m_pHeader->dwRealSize)
    {
		TraceError("LZObject: Size differs");
		return false;
    }

    return true;
}

bool CLZObject::Encrypt(DWORD * pdwKey) const
{
    if (!m_bCompressed)
    {
		assert(!"not compressed yet");
		return false;
    }

    BYTE * pbBuffer = m_pbBuffer + sizeof(THeader);
    m_pHeader->dwEncryptSize = tea_encrypt((DWORD *) pbBuffer, (const DWORD *) pbBuffer, pdwKey, m_pHeader->dwCompressedSize + 19);
    return true;
}

bool CLZObject::__Decrypt(DWORD * key, BYTE* data) const
{
    assert(m_pbBuffer);

    tea_decrypt((DWORD *) data, (const DWORD *) (m_pbIn - sizeof(DWORD)), key, m_pHeader->dwEncryptSize);
    return true;
}

void CLZObject::AllocBuffer(DWORD dwSrcSize)
{
    if (m_pbBuffer && !m_bInBuffer)
		gs_freeMemMgr.Free(m_pbBuffer, m_dwBufferSize);

    m_pbBuffer = gs_freeMemMgr.Alloc(dwSrcSize);
	m_dwBufferSize = dwSrcSize;
}

CLZO::CLZO() : m_pWorkMem(nullptr)
{
    if (lzo_init() != LZO_E_OK)
    {
		TraceError("LZO: cannot initialize");
		return;
    }

#if defined( LZO1X_999_MEM_COMPRESS )
    m_pWorkMem = (BYTE *) malloc(LZO1X_999_MEM_COMPRESS);
#else
    m_pWorkMem = (BYTE *) malloc(LZO1X_1_MEM_COMPRESS);
#endif

    if (nullptr == m_pWorkMem)
    {
		TraceError("LZO: cannot alloc memory");
		return;
    }
}

CLZO::~CLZO()
{
    if (m_pWorkMem)
    {
		free(m_pWorkMem);
		m_pWorkMem = nullptr;
    }
}

bool CLZO::CompressMemory(CLZObject & rObj, const void * pIn, UINT uiInLen) const
{
    rObj.BeginCompress(pIn, uiInLen);
    return rObj.Compress();
}

bool CLZO::CompressEncryptedMemory(CLZObject & rObj, const void * pIn, UINT uiInLen, DWORD * pdwKey) const
{
    rObj.BeginCompress(pIn, uiInLen);

    if (rObj.Compress())
    {
		if (rObj.Encrypt(pdwKey))
			return true;

		return false;
    }

    return false;
}

bool CLZO::Decompress(CLZObject & rObj, const BYTE * pbBuf, DWORD * pdwKey) const
{
    if (!rObj.BeginDecompress(pbBuf))
		return false;

    if (!rObj.Decompress(pdwKey))
		return false;

    return true;
}

BYTE * CLZO::GetWorkMemory() const
{
    return m_pWorkMem;
}

