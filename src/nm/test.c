
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
	int						ncmds;
	int						i;
	struct load_command		*lc;
	struct load_command		*lc_tmp;
	struct symtab_command	*sym;

	print(pute, av);
	ncmds = ((struct mach_header *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	lc_tmp = lc;
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			set_segment_32((struct segment_command *)lc, ptr);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (sym->strsize + sym->stroff > buf.st_size)
				handle_error("truncated or malformed objet");
			print_output_sort(sym, ptr, 0);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void		handle_64(char *ptr, struct stat buf, char *av, int pute)
{
	int						ncmds;
	int						i;
	struct load_command		*lc;
	struct load_command		*lc_tmp;
	struct symtab_command	*sym;

	print(pute, av);
	ncmds = ((struct mach_header_64 *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	lc_tmp = lc;
	i = -1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			set_segment_64((struct segment_command_64 *)lc, ptr);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (sym->strsize + sym->stroff > buf.st_size)
				handle_error("truncated or malformed objet");
			print_output_sort(sym, ptr, 0);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
