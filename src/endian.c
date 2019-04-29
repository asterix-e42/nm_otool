#include "nm_otool.h"

static char	g_endian = 0;

void		endian_mode(char is_endian)
{
	g_endian = is_endian;
}

uint16_t	endian2(uint16_t nb)
{
	return (g_endian ? ((nb & 0x00ff) << 8) | ((nb & 0xff00) >> 8) : nb);
}

uint32_t	endian4(uint32_t nb)
{
	return (g_endian ? ((nb & 0x000000ff) << 24)
						| ((nb & 0x0000ff00) << 8)
						| ((nb & 0x00ff0000) >> 8)
						| ((nb & 0xff000000) >> 24) : nb);
}

uint64_t	endian8(uint64_t nb)
{
	return (g_endian ? ((nb & 0xff00000000000000) >> 56)
						| ((nb & 0x00ff000000000000) >> 40)
						| ((nb & 0x0000ff0000000000) >> 24)
						| ((nb & 0x000000ff00000000) >> 8)
						| ((nb & 0x00000000ff000000) << 8)
						| ((nb & 0x0000000000ff0000) << 24)
						| ((nb & 0x000000000000ff00) << 40)
						| ((nb & 0x00000000000000ff) << 56) : nb);
}
