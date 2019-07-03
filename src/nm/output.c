/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:15:25 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/03 15:22:09 by tdumouli         ###   ########.fr       */
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
		tmp = (uint64_t)endian4(tab[i].n_value);
		putnb(&tmp, "", 8);
	}
	ft_putstr(" ");
	ft_putchar(symbol);
	ft_putstr(" ");
	ft_putendl_alnum(stringtable + endian4(tab[i].n_un.n_strx));
}

static void		print_output_64(int i, char *s_table, struct nlist_64 *tab)
{
	uint64_t	tmp;
	char		symbol;

	symbol = get_symbol_letter_64(tab[i]);
	if (symbol == 'U')
		write(1, "                ", 16);
	else if (symbol == '-')
		return ;
	else
	{
		tmp = (uint64_t)endian8(tab[i].n_value);
		putnb(&tmp, "", 0);
	}
	ft_putchar(' ');
	ft_putchar(symbol);
	ft_putchar(' ');
	ft_putendl_alnum(s_table + endian4(tab[i].n_un.n_strx));
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
			if (god(ptr + endian4(sym->stroff + tab[tmp[i[1]]].n_un.n_strx), 0))
				return (handle_error_free((void *)tmp));
			else if (ft_strcmp(ptr + endian4(sym->stroff +
			tab[tmp[i[1]]].n_un.n_strx),
			ptr + endian4(sym->stroff + tab[tmp[i[2]]].n_un.n_strx)) < 0)
				i[2] = i[1];
		print_output_32(tmp[i[2]], ptr + endian4(sym->stroff), tab);
		tmp[i[2]] = tmp[i[1] - 1];
	}
	free(tmp);
	return (EXIT_SUCCESS);
}

int				print_output_sort_64(struct symtab_command *sym, char *ptr)
{
	int				i[3];
	int				*tmp;
	struct nlist_64	*tab;

	tmp = ft_mallocf(sizeof(int) * (endian4(sym->nsyms) + 1));
	tab = (struct nlist_64 *)(ptr + endian4(sym->symoff));
	i[0] = endian4(sym->nsyms);
	while (--i[0] >= 0)
		tmp[i[0]] = i[0];
	while (++i[0] < (int)endian4(sym->nsyms))
	{
		i[1] = -1;
		i[2] = 0;
		while (++i[1] + i[0] < (int)endian4(sym->nsyms))
			if (god(ptr + endian4(sym->stroff + tab[tmp[i[1]]].n_un.n_strx), 0))
				return (handle_error("bad string index"));
			else if (ft_strcmp(ptr + endian4(sym->stroff +
			tab[tmp[i[1]]].n_un.n_strx),
			ptr + endian4(sym->stroff + tab[tmp[i[2]]].n_un.n_strx)) < 0)
				i[2] = i[1];
		print_output_64(tmp[i[2]], ptr + endian4(sym->stroff), tab);
		tmp[i[2]] = tmp[i[1] - 1];
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
