
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

void print_output(int i, char *stringtable, struct nlist_64 *array)
{
	char *ret;
	char symbol;

	symbol = get_symbol_letter(array[i]);
	if (symbol == 'U')
		write(1, "                ", 16);
	else if (symbol == '-')
		return ;
	else
		putnb(&(array[i].n_value), "");

	ft_putstr(" ");
	ft_putchar(symbol);
	ft_putstr(" ");

/*	ret = ft_itoabase(array[i].n_type, "0123456789abcdef");
	ft_putstr(ret);
	ft_putstr(" ");
	free(ret);
	ret = ft_itoabase(array[i].n_sect, "0123456789abcdef");
	ft_putstr(ret);
	ft_putstr(" ");
	free(ret);
	ret = ft_itoabase(array[i].n_desc, "0123456789abcdef");
	ft_putstr(ret);
	ft_putstr(" ");
	free(ret);
	ret = ft_itoabase(array[i].n_value, "0123456789abcdef");
	ft_putstr(ret);
	ft_putstr(" ");
	free(ret);
*/
	ft_putendl(stringtable + array[i].n_un.n_strx); //ok
}

void print_output_sort(int nsyms, int symoff, int stroff, char *ptr, struct stat buf)
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
		print_output(tmp[inc_g], stringtable, array);
		tmp[inc_g] = tmp[j - 1];
		i++;
	}
}
