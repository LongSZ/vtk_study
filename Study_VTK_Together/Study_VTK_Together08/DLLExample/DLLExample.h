#ifdef DLLEXAMPLE_DLL_API
#else
#define DLLEXAMPLE_DLL_API extern "C" _declspec(dllimport)
#endif

#include <windows.h>

DLLEXAMPLE_DLL_API int add(int a, int b);

DLLEXAMPLE_DLL_API int subtract(int a, int b);