
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

static void	print(int p, char *av)
{
	if (p > 2)
	{
		ft_putendl("");
		ft_putstr(av);
		ft_putendl(":");
	}
}

void		handle_32(char *ptr, struct stat buf, char *av, int pute)
{
	uint32_t				ncmds;
	uint32_t				inc;
	struct load_command		*lc;
	struct load_command		*lc_tmp;
	struct symtab_command	*sym;

	print(pute, av);
	ncmds = endian4(((struct mach_header *)ptr)->ncmds);
	lc = (void *)ptr + sizeof(struct mach_header);
	lc_tmp = lc;
	inc = -1;
	while (++inc < ncmds)
	{
		if (endian4(lc->cmd) == LC_SEGMENT)
			set_segment_32((struct segment_command *)lc, ptr);
		else if (endian4(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (endian4(sym->strsize) + endian4(sym->stroff) > buf.st_size)
				handle_error("truncated or malformed objet");
			print_output_sort_32(sym, ptr);
			break ;
		}
		lc = (void *)lc + endian4(lc->cmdsize);
	}
}

void		handle_64(char *ptr, struct stat buf, char *av, int pute)
{
	uint32_t				ncmds;
	uint32_t				inc;
	struct load_command		*lc;
	struct load_command		*lc_tmp;
	struct symtab_command	*sym;

	print(pute, av);
	ncmds = endian4(((struct mach_header_64 *)ptr)->ncmds);
	lc = (void *)ptr + sizeof(struct mach_header_64);
	lc_tmp = lc;
	inc = -1;
	while (++inc < ncmds)
	{
		if (endian4(lc->cmd) == LC_SEGMENT_64)
			set_segment_64((struct segment_command_64 *)lc, ptr);
		else if (endian4(lc->cmd) == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (endian4(sym->strsize) + endian4(sym->stroff) > buf.st_size)
				handle_error("truncated or malformed objet");
			print_output_sort_64(sym, ptr);
			break ;
		}
		lc = (void *)lc + endian8(lc->cmdsize);
	}
}
