
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

static void print_output_32(int i, char *stringtable, struct nlist *array)
{
	char *ret;
	char symbol;
	uint64_t tmp;

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

static void print_output_64(int i, char *stringtable, struct nlist_64 *array)
{
	char *ret;
	char symbol;

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
	ft_putendl(stringtable + array[i].n_un.n_strx);
}

void print_output_sort(int nsyms, int symoff, int stroff, char *ptr, struct stat buf, char _64)
{
	int i;
	int j;
	int inc_g;
	int *tmp;
	char *stringtable;
	struct nlist_64 *array; //semble identique , nop fini par 64


	tmp = malloc(sizeof(int) * (nsyms + 1));

	stringtable = ptr + stroff;
	array = (struct nlist_64 *)(ptr + symoff);
	i = -1;
	while(++i < nsyms)
		tmp[i] = i;
	i = 0;
	while (i < nsyms)
	{
		j = 0;
		inc_g = 0;
		while(j + i < nsyms)
		{
			if(ft_strcmp(stringtable + array[tmp[j]].n_un.n_strx, 
						stringtable + array[tmp[inc_g]].n_un.n_strx) < 0)
				inc_g = j;
			j++;
		}
		if (_64)
			print_output_32(tmp[inc_g], stringtable, (struct nlist *)array);
		else
			print_output_64(tmp[inc_g], stringtable, array);
		tmp[inc_g] = tmp[j - 1];
		i++;
	}
}
