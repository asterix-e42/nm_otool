/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:15:25 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/13 01:22:59 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

static void		print_output_32(int i, char *stringtable, struct nlist *tab)
{
	char		symbol;
	uint64_t	tmp;

	symbol = get_symbol_letter_32(((struct nlist *)tab)[i]);
	if (symbol == 'U')
		write(1, "        ", 8);
	else if (symbol == '-')
		return ;
	else
	{
		if (!(tmp = (uint64_t)(endian4(tab[i].n_value))) && !is_arch(0))
			return ;
		putnb(&tmp, "", 8);
	}
	ft_putstr(" ");
	ft_putchar(symbol);
	ft_putstr(" ");
	ft_putendl_alnum(stringtable + endian4(tab[i].n_un.n_strx));
}

int				sort_val_32(char *ptr, struct symtab_command *sym, int parcour,\
				int p2)
{
	int				ret;
	struct nlist	*tab;
	uint64_t		addr1;

	if (parcour == p2)
		return (1);
	tab = (struct nlist *)(ptr + endian4(sym->symoff));
	ret = ft_strcmp(ptr + endian4(sym->stroff) + \
			endian4(tab[parcour].n_un.n_strx), \
			ptr + endian4(sym->stroff) + \
			endian4(tab[p2].n_un.n_strx));
	if (ret)
		return (ret < 0);
	addr1 = (uint64_t)(endian4(tab[parcour].n_value));
	return (addr1 < (uint64_t)(endian4(tab[p2].n_value)));
}

int				print_output_sort_32(struct symtab_command *sym, char *ptr)
{
	int				i[3];
	int				*tmp;
	struct nlist	*tab;

	tmp = ft_mallocf(sizeof(int) * (endian4(sym->nsyms) + 1));
	tab = (struct nlist *)(ptr + endian4(sym->symoff));
	i[0] = endian4(sym->nsyms);
	while (--i[0] >= 0)
		tmp[i[0]] = i[0];
	while (++i[0] < (int)endian4(sym->nsyms))
	{
		i[1] = -1;
		i[2] = 0;
		while (++i[1] + i[0] < (int)endian4(sym->nsyms))
			if (god(ptr + endian4(sym->stroff) + \
			endian4(tab[tmp[i[1]]].n_un.n_strx), 0))
				return (handle_error_free((void *)tmp));
			else if (sort_val_32(ptr, sym, tmp[i[1]], tmp[i[2]]))
				i[2] = i[1];
		print_output_32(tmp[i[2]], ptr + endian4(sym->stroff), tab);
		tmp[i[2]] = tmp[i[1] - 1];
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
