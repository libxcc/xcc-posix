﻿#ifndef			_XCC_POSIX_STRING_H_
#define			_XCC_POSIX_STRING_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN



// posix : toupper
_XPOSIXAPI_ int __xcall__ x_posix_toupper(int _C);

// posix : tolower
_XPOSIXAPI_ int __xcall__ x_posix_tolower(int _C);





// posix : towupper
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towupper(wchar_t _C);

// posix : towlower
_XPOSIXAPI_ wchar_t __xcall__ x_posix_towlower(wchar_t _C);





// posix : strlen
_XPOSIXAPI_ size_t __xcall__ x_posix_strlen(const char* _String);

// posix : strcmp
_XPOSIXAPI_ int __xcall__ x_posix_strcmp(const char* _Str1, const char* _Str2);

// posix : stricmp
_XPOSIXAPI_ int __xcall__ x_posix_stricmp(const char* _Str1, const char* _Str2);

// posix : strcasecmp
_XPOSIXAPI_ int __xcall__ x_posix_strcasecmp(const char* _Str1, const char* _Str2);

// posix : strncmp
_XPOSIXAPI_ int __xcall__ x_posix_strncmp(const char* _Str1, const char* _Str2, size_t _Length);

// posix : strnicmp
_XPOSIXAPI_ int __xcall__ x_posix_strnicmp(const char* _Str1, const char* _Str2, size_t _Length);

// posix : strchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strchr(const char* _Str, int _Ch);

// posix : strichr
_XPOSIXAPI_ const char* __xcall__ x_posix_strichr(const char* _Str, int _Ch);

// posix : strrchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrchr(const char* _Str, int _Ch);

// posix : strirchr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirchr(const char* _Str, int _Ch);

// posix : strstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strstr(const char* _Str, const char* _SubStr);

// posix : stristr
_XPOSIXAPI_ const char* __xcall__ x_posix_stristr(const char* _Str, const char* _SubStr);

// posix : strrstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strrstr(const char* _Str, const char* _SubStr);

// posix : strirstr
_XPOSIXAPI_ const char* __xcall__ x_posix_strirstr(const char* _Str, const char* _SubStr);

// posix : strcpy
_XPOSIXAPI_ char* __xcall__ x_posix_strcpy(char* _Dst, const char* _Source);

// posix : strncpy
_XPOSIXAPI_ char* __xcall__ x_posix_strncpy(char* _Dst, const char* _Source, size_t _Length);

// posix : strcat
_XPOSIXAPI_ char* __xcall__ x_posix_strcat(char* _Str1, const char* _Str2);

// posix : strncat
_XPOSIXAPI_ char* __xcall__ x_posix_strncat(char* _Str1, const char* _Str2, size_t _Length);

// posix : strdup
_XPOSIXAPI_ char* __xcall__ x_posix_strdup(const char* _String);

// posix : strndup
_XPOSIXAPI_ char* __xcall__ x_posix_strndup(const char* _String, size_t _Length);

// posix : strupr
_XPOSIXAPI_ char* __xcall__ x_posix_strupr(char* _String);

// posix : strlwr
_XPOSIXAPI_ char* __xcall__ x_posix_strlwr(char* _String);

// posix : strrev
_XPOSIXAPI_ char* __xcall__ x_posix_strrev(char* _String);





// posix : wcslen
_XPOSIXAPI_ size_t __xcall__ x_posix_wcslen(const wchar_t* _String);

// posix : wcscmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsicmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsicmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcscasecmp
_XPOSIXAPI_ int __xcall__ x_posix_wcscasecmp(const wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsncmp
_XPOSIXAPI_ int __xcall__ x_posix_wcsncmp(const wchar_t* _Str1, const wchar_t* _Str2, size_t _Length);

// posix : wcschr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcschr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsichr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsichr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsrchr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsirchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsirchr(const wchar_t* _Str, wchar_t _Ch);

// posix : wcsstr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsstr(const wchar_t* _Str, const wchar_t* _SubStr);

// posix : wcsistr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wcsistr(const wchar_t* _Str, const wchar_t* _SubStr);

// posix : wcscpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscpy(wchar_t* _Dst, const wchar_t* _Source);

// posix : wcsncpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncpy(wchar_t* _Dst, const wchar_t* _Source, size_t _Length);

// posix : wcscat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcscat(wchar_t* _Str1, const wchar_t* _Str2);

// posix : wcsncat
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsncat(wchar_t* _Str1, const wchar_t* _Str2, size_t _Length);

// posix : wcsdup
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsdup(const wchar_t* _String);

// posix : wcsndup
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsndup(const wchar_t* _String, size_t _Length);

// posix : wcsupr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsupr(wchar_t* _String);

// posix : wcslwr
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcslwr(wchar_t* _String);

// posix : wcsrev
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wcsrev(wchar_t* _String);





// posix : strutow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_strutow(const char* _UTF8);

// posix : stratow
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_stratow(const char* _ASCII);

// posix : strwtou
_XPOSIXAPI_ char* __xcall__ x_posix_strwtou(const wchar_t* _UNICODE);

// posix : strwtoa
_XPOSIXAPI_ char* __xcall__ x_posix_strwtoa(const wchar_t* _UNICODE);





// posix : atof
_XPOSIXAPI_ double __xcall__ x_posix_atof(const char* _String);

// posix : atoi
_XPOSIXAPI_ int __xcall__ x_posix_atoi(const char* _String);

// posix : atol
_XPOSIXAPI_ long __xcall__ x_posix_atol(const char* _String);

// posix : atoll
_XPOSIXAPI_ long long __xcall__ x_posix_atoll(const char* _String);

// posix : strtof
_XPOSIXAPI_ float __xcall__ x_posix_strtof(const char* _String, char** _EndPtr);

// posix : strtod
_XPOSIXAPI_ double __xcall__ x_posix_strtod(const char* _String, char** _EndPtr);

// posix : strtold
_XPOSIXAPI_ long double __xcall__ x_posix_strtold(const char* _String, char** _EndPtr);

// posix : strtol
_XPOSIXAPI_ long __xcall__ x_posix_strtol(const char* _String, char** _EndPtr, int _Radix);

// posix : strtoul
_XPOSIXAPI_ unsigned long __xcall__ x_posix_strtoul(const char* _String, char** _EndPtr, int _Radix);

// posix : strtoll
_XPOSIXAPI_ long long __xcall__ x_posix_strtoll(const char* _String, char** _EndPtr, int _Radix);

// posix : strtoull
_XPOSIXAPI_ unsigned long long __xcall__ x_posix_strtoull(const char* _String, char** _EndPtr, int _Radix);





// 转换字符串至大写
_XPOSIXAPI_ char* __xcall__ x_posix_strtoupper(const char* _String);

// 转换字符串至小写
_XPOSIXAPI_ char* __xcall__ x_posix_strtolower(const char* _String);

// Replaces the specified character in the string
_XPOSIXAPI_ const char* __xcall__ x_string_replace_char(char* _String, char _Src, char _Dest);

// Replaces the specified character in the string
_XPOSIXAPI_ const wchar_t* __xcall__ x_string_replace_wchar_t(wchar_t* _String, wchar_t _Src, wchar_t _Dest);



/// 根据vsnprintf请求合适的内存格式字符串
/// \param _Format : 包含格式字符串的 C 字符串，该格式字符串遵循与 printf 中的格式相同的规范（有关详细信息，请参阅 printf）。
/// \param ... : 根据格式字符串，该函数可能需要一系列附加参数
/// \return : 如果成功则返回格式化的字符串指针，如果失败则返回null。 需要调用x_posix_free()释放
_XPOSIXAPI_ char* __xcall__ x_string_format(const char* _Format, ...);

/// 根据vsnprintf请求合适的内存格式字符串
/// \param _Format : 包含格式字符串的 C 字符串，该格式字符串遵循与 printf 中的格式相同的规范（有关详细信息，请参阅 printf）。
/// \param _ArgList : 参数列表
/// \return : 如果成功则返回格式化的字符串指针，如果失败则返回null。 需要调用x_posix_free()释放
_XPOSIXAPI_ char* __xcall__ x_string_vformat(const char* _Format, va_list _ArgList);



XCC_CXX_EXTERN_END

#endif
