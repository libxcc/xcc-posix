#ifndef			_XCC_POSIX_ENDIAN_H_
#define			_XCC_POSIX_ENDIAN_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN



// Check whether the operating system is in big-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_big();

// Check whether the operating system is in little-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_little();





// reverse byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_revs(unsigned short _Number);

// reverse byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_revi(unsigned int _Number);

// reverse byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_revl(unsigned long _Number);

// reverse byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_revll(unsigned long long _Number);





// Conversion from native byte order to network byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htons(unsigned short _Number);

// Conversion from native byte order to network byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htoni(unsigned int _Number);

// Conversion from native byte order to network byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htonl(unsigned long _Number);

// Conversion from native byte order to network byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htonll(unsigned long long _Number);





// Convert from native byte order to little endian byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htols(unsigned short _Number);

// Convert from native byte order to little endian byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htoli(unsigned int _Number);

// Convert from native byte order to little endian byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htoll(unsigned long _Number);

// Convert from native byte order to little endian byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htolll(unsigned long long _Number);





// Convert from native byte order to big endian byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htobs(unsigned short _Number);

// Convert from native byte order to big endian byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htobi(unsigned int _Number);

// Convert from native byte order to big endian byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htobl(unsigned long _Number);

// Convert from native byte order to big endian byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htobll(unsigned long long _Number);





// Conversion from network byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_ntohs(unsigned short _Number);

// Conversion from network byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_ntohi(unsigned int _Number);

// Conversion from network byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_ntohl(unsigned long _Number);

// Conversion from network byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_ntohll(unsigned long long _Number);





// Conversion from little endian byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_ltohs(unsigned short _Number);

// Conversion from little endian byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_ltohi(unsigned int _Number);

// Conversion from little endian byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_ltohl(unsigned long _Number);

// Conversion from little endian byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_ltohll(unsigned long long _Number);





// Conversion from big endian byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_btohs(unsigned short _Number);

// Conversion from big endian byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_btohi(unsigned int _Number);

// Conversion from big endian byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_btohl(unsigned long _Number);

// Conversion from big endian byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_btohll(unsigned long long _Number);



XCC_CXX_EXTERN_END

#endif
