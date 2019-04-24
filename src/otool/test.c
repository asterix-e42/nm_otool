
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

void handle_64(char *ptr, struct stat buf)
{
	int		ncmds;
	int		i;
	struct mach_header_64	*header; //meme que 32
	struct load_command	*lc;
	struct load_command	*lc_tmp;
	struct symtab_command	*sym;
	char *s;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;//
	i = -1;
	while (++i < ncmds)
	{
		
		if (lc->cmd == LC_SEGMENT_64)// symbol
		{
			set_segment(lc, ptr);		
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
