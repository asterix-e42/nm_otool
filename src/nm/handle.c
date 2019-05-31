/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:14:54 by tdumouli          #+#    #+#             */
/*   Updated: 2019/05/31 15:57:00 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	call_print(struct symtab_command *sym, struct stat buf, void *ptr,
		int print_sort(struct symtab_command *, char *, struct stat))
{
	if (endian4(sym->strsize) + endian4(sym->stroff) > buf.st_size)
		return (handle_error("truncated or malformed objet"));
	if (print_sort(sym, ptr, buf))
		return (handle_error("truncated or malformed objet, symbol"));
	return (EXIT_SUCCESS);
}

int			handle_32(void *ptr, struct stat buf, char *av, int pute)
{
	uint32_t				ncmds;
	uint32_t				inc;
	struct load_command		*lc;

	print(pute, av);
	ncmds = endian4(((struct mach_header *)ptr)->ncmds);
	lc = (void *)ptr + sizeof(struct mach_header);
	inc = -1;
	while (++inc < ncmds)
	{
		if (endian4(lc->cmd) == LC_SEGMENT)
		{
			if (set_segment_32((struct segment_command *)lc, ptr))
				return (handle_error("error segment"));
		}
		else if (endian4(lc->cmd) == LC_SYMTAB)
			if (call_print((void *)lc, buf, ptr, print_output_sort_32))
				return (EXIT_FAILURE);
		if ((void *)(lc = (void *)lc + endian4(lc->cmdsize)) >
				(buf.st_size + ptr))
			return (handle_error("The file was not recognized as valid"));
	}
	return (EXIT_SUCCESS);
}

int			handle_64(void *ptr, struct stat buf, char *av, int pute)
{
	uint32_t				ncmds;
	uint32_t				inc;
	struct load_command		*lc;

	print(pute, av);
	ncmds = endian4(((struct mach_header_64 *)ptr)->ncmds);
	lc = (void *)ptr + sizeof(struct mach_header_64);
	inc = -1;
	while (++inc < ncmds)
	{
		if (endian4(lc->cmd) == LC_SEGMENT_64)
		{
			if (set_segment_64((struct segment_command_64 *)lc, ptr))
				return (handle_error("error segment"));
		}
		else if (endian4(lc->cmd) == LC_SYMTAB)
			if (call_print((void *)lc, buf, ptr, print_output_sort_64))
				return (EXIT_FAILURE);
		if ((void *)(lc = (void *)lc + endian8(lc->cmdsize)) >
				(buf.st_size + ptr))
			return (handle_error("The file was not recognized as valid"));
	}
	return (EXIT_SUCCESS);
}
