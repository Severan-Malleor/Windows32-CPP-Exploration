#include <Windows.h>
#include <iostream>
#include <format>
#include <string>

/*
    https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamew
    Retrieves the NetBIOS name of the local computer. This name is established at system startup, 
    when the system reads it from the registry.

    BOOL GetComputerNameW(
      [out]     LPWSTR  lpBuffer,
      [in, out] LPDWORD nSize
    );

    GetComputerName retrieves only the NetBIOS name of the local computer. 
    To retrieve the DNS host name, DNS domain name, or the fully qualified DNS name, 
    call the GetComputerNameEx function.
    https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getcomputernameexw

*/



namespace utils {
    // computerName is a pointer (array of wide chars)
    int displaySpecs(wchar_t* computerName, DWORD computerNameSize) {

        // wide string type and wide literal prefix, 
        // required for MessageBoxW which expects LPCWSTR (const wchar_t*)

        std::wstring msg = std::format(L"Computer Name: {}\nName(NetBIOS) MAX size length: {}", computerName, computerNameSize);

        // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messageboxw
        MessageBoxW(NULL, msg.c_str(), L"System Specs", MB_OK);
        return 0;
    }
}

int main() {
    // Wide char array since we are using the UNICODE wide function.
    // The buffer size should be large enough to contain MAX_COMPUTERNAME_LENGTH + 1 characters.
    wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];


    /*
        input, specifies the size of the buffer
        If the buffer is too small, the function fails and GetLastError returns ERROR_BUFFER_OVERFLOW.
    */
    
    DWORD computerNameSize = MAX_COMPUTERNAME_LENGTH + 1;
    
     bool hasComputerName = GetComputerNameW(computerName, &computerNameSize);

     if (hasComputerName) {
         utils::displaySpecs(computerName, computerNameSize);
     }
     else {
         DWORD err = GetLastError();

         wchar_t buffer[512] = { 0 };

         FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, 0, buffer, 512, NULL);

         std::wcout << L"Error " << err << L": " << buffer << std::endl;
     }
}

