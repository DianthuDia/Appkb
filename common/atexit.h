#pragma once
// デストラクタをCRTを使用しないで使用できるようにする

#ifdef NO_CRT

typedef void (__cdecl* vfuncv)(void);

// VCではこれらのセグメントに初期化処理を行う関数へのポインタを格納する
extern "C"{
#pragma data_seg(".CRT$XIA")
	static vfuncv __xi_a[] = {NULL}; 
#pragma data_seg(".CRT$XIZ")
	static vfuncv __xi_z[] = {NULL}; 
#pragma data_seg(".CRT$XCA")
	static vfuncv __xc_a[] = {NULL}; 
#pragma data_seg(".CRT$XCZ")
	static vfuncv __xc_z[] = {NULL}; 
#pragma data_seg()
}

// VCで自動生成された初期化処理を行う関数内では終了処理をatexitを呼んで登録している
#define EXITFUNCS_BOUNDARY 8
static vfuncv* __exit_a = NULL;
static vfuncv* __exit_z = NULL;
static vfuncv* __exit_zz = NULL;

static void _callfunclist(vfuncv* pBegin, vfuncv* pEnd)
{
	while (pBegin < pEnd)
	{
		if (*pBegin != NULL)
			(**pBegin)(); 
		++pBegin;
	}
}

extern "C" int atexit(vfuncv pf)
{
	if (pf == NULL)
		return 0;
	if (__exit_z == __exit_zz)
	{
		const size_t nSize = __exit_zz - __exit_a;
//		vfuncv* new_funcs = new vfuncv[nSize + EXITFUNCS_BOUNDARY];
		vfuncv* new_funcs = (vfuncv*)HeapAlloc(::GetProcessHeap(),HEAP_GENERATE_EXCEPTIONS,sizeof(vfuncv)*(nSize + EXITFUNCS_BOUNDARY));
		if (new_funcs == NULL)
			return -1; 
		vfuncv* pfDst = new_funcs;
		if (__exit_a != NULL)
		{
			vfuncv* pfSrc = __exit_a;
			size_t nCount = nSize;
			while (--nCount)
				*pfDst++ = *pfSrc++; 
//			delete[] __exit_a;
			::HeapFree(::GetProcessHeap(),0,__exit_a);
		}
		unsigned char nCount = EXITFUNCS_BOUNDARY;
		while (--nCount)
			*pfDst++ = NULL; 
		__exit_a = new_funcs;
		__exit_z = __exit_a + nSize;
		__exit_zz = __exit_z + EXITFUNCS_BOUNDARY;

	}
	*__exit_z++ = pf;
	return 0;
}

#endif	// NO_CRT
