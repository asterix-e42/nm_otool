
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

void handle_64(char *ptr, struct stat buf, char *av, int pute)
{
	int		ncmds;
	int		i;
	struct mach_header_64	*header; //meme que 32
	struct load_command	*lc;
	struct load_command	*lc_tmp;
	struct symtab_command	*sym;

	if (pute > 2)
	{
		ft_putendl("");
		ft_putstr(av);
		ft_putendl(":");
	}
	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;//
	for(i = 0; i < ncmds; ++i)
	{
		
		if (lc->cmd == LC_SEGMENT_64)
		{
			set_segment_64((struct segment_command_64 *)lc, ptr);		
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if(sym->strsize + sym->stroff > buf.st_size)
				handle_error("truncated or malformed objet");
			print_output_sort(sym->nsyms, sym->symoff, sym->stroff, ptr, buf, 0);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
