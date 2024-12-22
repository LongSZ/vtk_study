#define DLLEXAMPLE_DLL_API extern "C" _declspec(dllexport)

#include "DLLExample.h"

DLLEXAMPLE_DLL_API int add(int a, int b)
{
	return a+b;
}

DLLEXAMPLE_DLL_API int subtract(int a, int b)
{
	return a-b;
}