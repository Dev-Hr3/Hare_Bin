#ifndef __INC_CRC32_H__
#define __INC_CRC32_H__

#include <windows.h>

DWORD GetCRC32(const char* buffer, size_t count);
DWORD GetCaseCRC32(const char * buf, size_t len);
DWORD GetHFILECRC32(HANDLE hFile);
DWORD GetFileCRC32(const char* c_szFileName);
DWORD GetFileSize(const char* c_szFileName);

#endif
//martysama0134's a288e6779da68f768431f9975e780da3
