#include <iostream>
#include <Windows.h>
#include "utils.h"
#include <format>
#include <string>

/*
	https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew

	Kind of like GetComputerName. Takes the same types, a 
	
	* LPWSTR (wchar_t*)
		* A buffer size of (UNLEN + 1) characters will hold the maximum length 
		user name including the terminating null character.
		* UNLEN = Constant of 256
		* https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-tsch/165836c1-89d7-4abb-840d-80cf2510aa3e
		* Kind of like how we used MAX_COMPUTERNAME_LENGTH but a username can be longer of UNLEN + 1 length

	BOOL GetUserNameW(
	  [out]     LPWSTR  lpBuffer,
	  [in, out] LPDWORD pcbBuffer
	);

*/



namespace utils {
	int displayUser(wchar_t* userName) {

		std::wstring msg = std::format(L"Hello, {}", userName);

		MessageBoxW(NULL, msg.c_str(), msg.c_str(), MB_OK);

		return 0;

	}

	void displayError() {
		DWORD err = GetLastError();

		wchar_t buffer[512] = { 0 };

		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, 0, buffer, 512, NULL);

		MessageBoxW(NULL, buffer, L"Error", MB_OK);


	}
}

int main() {

	wchar_t userName[256 + 1];
	DWORD userNameSize = 256 + 1;

	bool hasUserName = GetUserNameW(userName, &userNameSize);

	if (hasUserName) {
		utils::displayUser(userName);
	}
	else {
		utils::displayError();
	}

}