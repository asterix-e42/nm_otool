#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

void	handle_32(char *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			inc;
	struct mach_header		*header;
	struct load_command		*lc;
	struct load_command		*lc_tmp;

	(void)pute;
	(void)buf;
	ft_putstr(av);
	ft_putendl(":");
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;
	inc = -1;
	while (++inc < endian4(header->ncmds))
	{
		if (endian4(lc->cmd) == LC_SEGMENT)
			set_segment_32((struct segment_command *)lc, ptr);
		lc = (void *)lc + endian4(lc->cmdsize);
	}
}

void	handle_64(char *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			inc;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct load_command		*lc_tmp;

	(void)pute;
	(void)buf;
	ft_putstr(av);
	ft_putendl(":");
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;
	inc = -1;
	while (++inc < endian4(header->ncmds))
	{
		if (endian4(lc->cmd) == LC_SEGMENT_64)
			set_segment_64((struct segment_command_64 *)lc, ptr);
		lc = (void *)lc + endian4(lc->cmdsize);
	}
}
