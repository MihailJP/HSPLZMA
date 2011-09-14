#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include "hsp3plugin.h"
#include "LzmaLib.h"

#define HSPLZMA_PADDING_SIZE 8

EXPORT BOOL WINAPI lzma_compress(HSPEXINFO *hei)
{
	unsigned char* dest = (unsigned char *)hei->HspFunc_prm_getv();
	unsigned int destBufSize = hei->HspFunc_prm_geti();
	unsigned char* source = (unsigned char *)hei->HspFunc_prm_getv();
	unsigned int sourceLen = hei->HspFunc_prm_geti();
	unsigned PropsSize = LZMA_PROPS_SIZE;
	int level = hei->HspFunc_prm_getdi(-1);
	int sizeFac = hei->HspFunc_prm_getdi(-1);
	int lc = hei->HspFunc_prm_getdi(-1);
	int lp = hei->HspFunc_prm_getdi(-1);
	int pb = hei->HspFunc_prm_getdi(-1);
	int fb = hei->HspFunc_prm_getdi(-1);
	int numThreads = hei->HspFunc_prm_getdi(2);
	size_t* destLen = &destBufSize;
	int ret;
	unsigned dictSize;

	if (*hei->er) return *hei->er;
	if (sizeFac == -1) {
		dictSize = 0;
	} else {
		if (sizeFac%2) {
			dictSize = 3 << ((int)(sizeFac/2));
		} else {
			dictSize = 1 << ((int)(sizeFac/2+1));
		}
	}
	ret = LzmaCompress(&dest[LZMA_PROPS_SIZE+HSPLZMA_PADDING_SIZE], destLen, source, sourceLen, &dest[0], &PropsSize, level, dictSize, lc, lp, pb, fb, numThreads);
	if (ret == SZ_OK) {
		*hei->strsize = *destLen + LZMA_PROPS_SIZE + HSPLZMA_PADDING_SIZE;
		for (int i=0;i<HSPLZMA_PADDING_SIZE;i++) dest[LZMA_PROPS_SIZE + i] = 0xff;
	}
	return -(abs(ret));
}

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
