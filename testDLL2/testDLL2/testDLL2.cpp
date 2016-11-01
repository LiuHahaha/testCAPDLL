// testDLL2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"

int _tmain(int argc, _TCHAR* argv[])
{
	typedef int (* MYPROC)(); 
	HMODULE hdll_lib =::LoadLibraryEx(TEXT("testCAPDLL1.dll"),NULL,0); 
	MYPROC pFunc=(MYPROC)GetProcAddress(hdll_lib, "doCAPDecode");
	int a=pFunc();
	FreeLibrary(hdll_lib); 
	printf("OK!");
	return 0;
}

