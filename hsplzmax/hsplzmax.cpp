#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include "hsp3plugin.h"
#include "LzmaLib.h"

#define HSPLZMA_PADDING_SIZE 8

EXPORT BOOL WINAPI lzma_decompress(HSPEXINFO *hei)
{
	unsigned char* dest = (unsigned char *)hei->HspFunc_prm_getv();
	unsigned int destBufSize = hei->HspFunc_prm_geti();
	unsigned char* source = (unsigned char *)hei->HspFunc_prm_getv();
	unsigned int slen = hei->HspFunc_prm_geti() - LZMA_PROPS_SIZE;
	size_t* destLen = &destBufSize;
	size_t* sourceLen = &slen;
	size_t PropsSize = LZMA_PROPS_SIZE;
	int ret;

	if (*hei->er) return *hei->er;
	ret = LzmaUncompress(dest, destLen, &source[LZMA_PROPS_SIZE+HSPLZMA_PADDING_SIZE], sourceLen, &source[0], PropsSize);
	if (ret == SZ_ERROR_INPUT_EOF) ret = SZ_OK; /* Ignore this error */
	if (ret == SZ_OK) *hei->strsize = *destLen;
	return -(abs(ret));
}
