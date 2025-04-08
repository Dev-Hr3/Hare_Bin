#pragma once

BOOL ShiftJIS_IsLeadByte( const char chByte );
BOOL ShiftJIS_IsTrailByte( const char chByte );
int ShiftJIS_StringCompareCI( LPCSTR szStringLeft, LPCSTR szStringRight, size_t sizeLength );
//martysama0134's a288e6779da68f768431f9975e780da3
