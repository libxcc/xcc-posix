#include <xcc-posix/endian.h>



// Check whether the operating system is in big-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_big()
{
	return !x_endian_is_little();
}

// Check whether the operating system is in little-endian order
_XPOSIXAPI_ bool __xcall__ x_endian_is_little()
{
	union UCheck_Little
	{
		int		_VALUE4;
		char		_VALUE1;
	}_ValueLittle;
	_ValueLittle._VALUE4 = 1;
	// The big-endian returns 0 and the little-endian returns 1
	return _ValueLittle._VALUE1 == 1;
}





// reverse byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_revs(unsigned short _Number)
{
	return (((_Number & 0xFF00U) >> 8) | ((_Number & 0x00FFU) << 8));
}

// reverse byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_revi(unsigned int _Number)
{
	return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
}

// reverse byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_revl(unsigned long _Number)
{
	bool		vLongBit4 = sizeof(unsigned long) == sizeof(unsigned int);
	if(vLongBit4)
	{
		return (((_Number & 0xFF000000U) >> 24) | ((_Number & 0x00FF0000U) >> 8) | ((_Number & 0x0000FF00U) << 8) | ((_Number & 0x000000FFU) << 24));
	}
	else
	{
		return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
			((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
			((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
			((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
	}
}

// reverse byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_revll(unsigned long long _Number)
{
	return (((_Number & 0x00000000000000FFULL) << 56) | ((_Number & 0x000000000000FF00ULL) << 40) |
		((_Number & 0x0000000000FF0000ULL) << 24) | ((_Number & 0x00000000FF000000ULL) << 8) |
		((_Number & 0x000000FF00000000ULL) >> 8) | ((_Number & 0x0000FF0000000000ULL) >> 24) |
		((_Number & 0x00FF000000000000ULL) >> 40) | ((_Number & 0xFF00000000000000ULL) >> 56));
}





// Conversion from native byte order to network byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htons(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htoni(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htonl(unsigned long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Conversion from native byte order to network byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htonll(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}





// Convert from native byte order to little endian byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htols(unsigned short _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Convert from native byte order to little endian byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htoli(unsigned int _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Convert from native byte order to little endian byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htoll(unsigned long _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Convert from native byte order to little endian byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htolll(unsigned long long _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}





// Convert from native byte order to big endian byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_htobs(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Convert from native byte order to big endian byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_htobi(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Convert from native byte order to big endian byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_htobl(unsigned long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Convert from native byte order to big endian byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_htobll(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}





// Conversion from network byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_ntohs(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_ntohi(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_ntohl(unsigned long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Conversion from network byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_ntohll(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}





// Conversion from little endian byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_ltohs(unsigned short _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Conversion from little endian byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_ltohi(unsigned int _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Conversion from little endian byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_ltohl(unsigned long _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Conversion from little endian byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_ltohll(unsigned long long _Number)
{
	if(x_endian_is_big())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}





// Conversion from big endian byte order to native byte order : ushort
_XPOSIXAPI_ unsigned short __xcall__ x_endian_btohs(unsigned short _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revs(_Number);
	}
	return _Number;
}

// Conversion from big endian byte order to native byte order : uint
_XPOSIXAPI_ unsigned int __xcall__ x_endian_btohi(unsigned int _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revi(_Number);
	}
	return _Number;
}

// Conversion from big endian byte order to native byte order : ulong
_XPOSIXAPI_ unsigned long __xcall__ x_endian_btohl(unsigned long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revl(_Number);
	}
	return _Number;
}

// Conversion from big endian byte order to native byte order : ullong
_XPOSIXAPI_ unsigned long long __xcall__ x_endian_btohll(unsigned long long _Number)
{
	if(x_endian_is_little())
	{
		return x_endian_revll(_Number);
	}
	return _Number;
}
