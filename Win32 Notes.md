# Integer types

|Data type|Size|Signed?|
|---|---|---|
|**BYTE**|8 bits|Unsigned|
|**DWORD**|32 bits|Unsigned|
|**INT32**|32 bits|Signed|
|**INT64**|64 bits|Signed|
|**LONG**|32 bits|Signed|
|**LONGLONG**|64 bits|Signed|
|**UINT32**|32 bits|Unsigned|
|**UINT64**|64 bits|Unsigned|
|**ULONG**|32 bits|Unsigned|
|**ULONGLONG**|64 bits|Unsigned|
|**WORD**|16 bits|Unsigned|
# Working with Strings

|Macro|Unicode|ANSI|
|---|---|---|
|TCHAR|`wchar_t`|`char`|
|`TEXT("x")` or `_T("x")`|`L"x"`|`"x"`|

|Typedef|Definition|
|---|---|
|**CHAR**|`char`|
|**PSTR** or **LPSTR**|`char*`|
|**PCSTR** or **LPCSTR**|`const char*`|
|**PWSTR** or **LPWSTR**|`wchar_t*`|
|**PCWSTR** or **LPCWSTR**|`const wchar_t*`|

|Annotation|Meaning|Who provides the memory?|
|---|---|---|
|**[in]**|Input parameter. The function **reads** from it.|**You** (caller)|
|**[out]**|Output parameter. The function **writes** to it.|**You** (caller)|
|**[in, out]**|Both input and output. Function reads it, then writes back to it.|**You** (caller)|
|**[in, optional]**|Input, but can be `NULL`.|**You**|
