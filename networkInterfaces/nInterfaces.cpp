#include <Windows.h>
#include <iostream>
#include <iphlpapi.h> // Tells the compiler where the function declarations are.

// Tells the linker to link against the actual library.
// Method only works with Visual Studio / MSVC
// If you ever switch to MinGW, CMake, or another compiler, you'll need to link differently (e.g., -liphlpapi)
#pragma comment(lib, "iphlpapi.lib") 



int main() {
	/*
		IPHLPAPI_DLL_LINKAGE DWORD GetInterfaceInfo(
		  A pointer to a buffer that specifies an IP_INTERFACE_INFO structure that receives the list of adapters.
		  [out]     PIP_INTERFACE_INFO pIfTable,

		  A pointer to a DWORD variable that specifies the size of the buffer pointed to by pIfTable parameter to receive the IP_INTERFACE_INFO structure.
		  [in, out] PULONG             dwOutBufLen
		);

		typedef struct _IP_INTERFACE_INFO {
		  LONG                 NumAdapters;
		  IP_ADAPTER_INDEX_MAP Adapter[1];
		} IP_INTERFACE_INFO, *PIP_INTERFACE_INFO;
	*/

	// https://learn.microsoft.com/en-us/windows/win32/api/iphlpapi/nf-iphlpapi-getinterfaceinfo
	// https://learn.microsoft.com/en-us/windows/win32/api/ipexport/ns-ipexport-ip_interface_info
	 PIP_INTERFACE_INFO pInfo = nullptr;

	 ULONG ulOutBuflen = 0;
	 DWORD dwRetVal = 0;


	 // First call - Intentionally fails to discover required buffer size
	 // This is called a two-call pattern
	 	 
	 // If this size is insufficient to hold the IPv4 interface information, 
	 // GetInterfaceInfo fills in this variable with the required size, 
	 // and returns an error code of ERROR_INSUFFICIENT_BUFFER.
	 dwRetVal = GetInterfaceInfo(NULL, &ulOutBuflen);

	 if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) { // which it will first call
		 
		 // Since we do not know the size at compile time, we need to allocate memory with the new space that
		 // was written ([in, out] PULONG dwOutBufLen) by the function. REMEMBER TO FREE!!!
		 pInfo = (PIP_INTERFACE_INFO)malloc(ulOutBuflen);

		 if (pInfo == nullptr) {
			 return 1;
		 }

		 // Second call WITH THE KNOWN size.
		 dwRetVal = GetInterfaceInfo(pInfo, &ulOutBuflen);
	 }

	 // NO_ERROR is a macro that represents a constant value of 0L, typically used to indicate 
	 // the absence of errors in a program.
	 if (dwRetVal == NO_ERROR) {
		 std::wcout << L"Number of Adapters: " << pInfo->NumAdapters << std::endl;

		 for (int i = 0; i < pInfo->NumAdapters; ++i) {
			 std::wcout << L"Adapter[" << i << L"]: " << pInfo->Adapter[i].Name << std::endl;
		 }

	 }
	 else {
		 std::wcout << L"GetInterfaceInfo failed with error: " << dwRetVal << std::endl;
	 }

	 if (pInfo) {
		 free(pInfo);
	 }

	 return 0;


}