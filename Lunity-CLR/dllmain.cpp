// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <metahost.h>
#pragma comment(lib, "mscoree.lib")

DWORD WINAPI startClr(LPVOID lpParam)
{
	ICLRMetaHost* metaHost = NULL; //Declare our CLR Meta Host value as a NULL
	ICLRRuntimeInfo* runtimeInfo = NULL; //Declare our CLR Runtime Info as a Null
	ICLRRuntimeHost* runtimeHost = NULL; //Delcare our CLR HOST as a NULL

	if (CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&metaHost) == S_OK) //If Creating CLR Instance with follow parameters is successful
		if (metaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (LPVOID*)&runtimeInfo) == S_OK) //If getting Runtime version is successful
			if (runtimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_ICLRRuntimeHost, (LPVOID*)&runtimeHost) == S_OK) //If getting the interface with the follow parameters is successful
				if (runtimeHost->Start() == S_OK) //Start the CLR (If it is successful)
				{
					DWORD pReturnValue; //Declare our return value as a DWORD

					//Invoke our method through CLR host using following parameters
					runtimeHost->ExecuteInDefaultAppDomain(L"A:\\Desktop Files\\Minecraft Stuff\\Bedrock Modding\\Lunity\\Lunity-Injectable\\bin\\Debug\\Lunity-Injectable.dll", L"Lunity_Injectable.EntryClass", L"Main", L"Hello!", &pReturnValue);

					//OPTIONAL: You can keep the CLR Opened depending on your needs
					runtimeInfo->Release();
					metaHost->Release();
					runtimeHost->Release();
				}
	return 0;
}

BOOL __stdcall DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startClr, hModule, NULL, NULL);
        DisableThreadLibraryCalls(hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

