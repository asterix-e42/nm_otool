
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

static void		print_output_32(int i, char *stringtable, struct nlist *array)
{
	char		symbol;
	uint64_t	tmp;

	symbol = get_symbol_letter(((struct nlist_64 *)array)[i]);
	if (symbol == 'U')
		write(1, "                ", 16);
	else if (symbol == '-')
		return ;
	else
	{
		tmp = (uint64_t)array[i].n_value;
		putnb(&tmp, "", 8);
	}
	ft_putstr(" ");
	ft_putchar(symbol);
	ft_putstr(" ");
	ft_putendl(stringtable + array[i].n_un.n_strx);
}

static void		print_output_64(int i, char *s_table, struct nlist_64 *array)
{
	char		symbol;

	symbol = get_symbol_letter(array[i]);
	if (symbol == 'U')
		write(1, "                ", 16);
	else if (symbol == '-')
		return ;
	else
		putnb(&(array[i].n_value), "", 0);
	ft_putstr(" ");
	ft_putchar(symbol);
	ft_putstr(" ");
	ft_putendl(s_table + array[i].n_un.n_strx);
}

void			print_output_sort(struct symtab_command *sym, char *ptr,
		char is_64)
{
	unsigned int	inc[3];
	int				*tmp;
	char			*stringtable;
	struct nlist_64	*array;

	tmp = malloc(sizeof(int) * (sym->nsyms + 1));
	stringtable = ptr + sym->stroff;
	array = (struct nlist_64 *)(ptr + sym->symoff);
	inc[0] = sym->nsyms;
	while (--inc[0] > 0)
		tmp[inc[0]] = inc[0];
	while (++inc[0] < sym->nsyms)
	{
		inc[1] = -1;
		inc[2] = 0;
		while (++inc[1] + inc[0] < sym->nsyms)
			if (ft_strcmp(stringtable + array[tmp[inc[1]]].n_un.n_strx,
						stringtable + array[tmp[inc[2]]].n_un.n_strx) < 0)
				inc[2] = inc[1];
		if (is_64)
			print_output_32(tmp[inc[2]], stringtable, (struct nlist *)array);
		else
			print_output_64(tmp[inc[2]], stringtable, array);
		tmp[inc[2]] = tmp[inc[1] - 1];
	}
}
