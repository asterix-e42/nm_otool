
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

	printf("dfs\n");
	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;//
	for(i = 0; i < ncmds; ++i)
	{
		
		if (lc->cmd == LC_SEGMENT_64)// nm symbol
		{
			set_segment(lc, ptr);		
		}
		if (lc->cmd == LC_SYMTAB)// nm interet !!
		{
			sym = (struct symtab_command *)lc;
			if(sym->strsize + sym->stroff > buf.st_size)
				handle_error("truncated or malformed object (stroff field plus strsize field of LC_SYMTAB command 2 extends past the end of the file)");
			print_output_sort(sym->nsyms, sym->symoff, sym->stroff, ptr, buf);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
