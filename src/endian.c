


#include "nm_otool.h"

uint16_t endian2(uint16_t nb)
{
	return (((nb & 0x00ff) << 8) | ((nb & 0xff00) >> 8));
}

uint32_t endian4(uint32_t nb)
{
	return (((nb & 0x000000ff) << 16) | ((nb & 0x0000ff00) >> 8)
	| ((nb & 0x00ff0000) << 8) | ((nb & 0xff000000) >> 16));
}

uint64_t endian8(uint64_t nb)
{
	return (((nb & 0xff00000000000000) >> 56)
			| ((nb & 0x00ff000000000000) >> 40)
			| ((nb & 0x0000ff0000000000) >> 24)
			| ((nb & 0x000000ff00000000) >> 8)
			| ((nb & 0x00000000ff000000) << 8)
			| ((nb & 0x0000000000ff0000) << 24)
			| ((nb & 0x000000000000ff00) << 40)
			| ((nb & 0x00000000000000ff) << 56));
}
