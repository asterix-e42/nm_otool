/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:13:36 by tdumouli          #+#    #+#             */
/*   Updated: 2019/05/30 23:33:39 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"

int		handle_32(void *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			inc;
	struct mach_header		*header;
	struct load_command		*lc;
	struct load_command		*lc_tmp;

	(void)pute;
	(void)buf;
	ft_putstr(av);
	ft_putendl(":");
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;
	inc = -1;
	while (++inc < endian4(header->ncmds))
	{
		if (endian4(lc->cmd) == LC_SEGMENT)
			if (set_segment_32((struct segment_command *)lc, ptr))
				return (EXIT_FAILURE);
		if ((void *)(lc = lc + endian4(lc->cmdsize)) > (buf.st_size + ptr))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		handle_64(void *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			inc;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct load_command		*lc_tmp;

	(void)pute;
	(void)buf;
	ft_putstr(av);
	ft_putendl(":");
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	lc_tmp = lc;
	inc = -1;
	while (++inc < endian4(header->ncmds))
	{
		if (endian4(lc->cmd) == LC_SEGMENT_64)
			if (set_segment_64((struct segment_command_64 *)lc, ptr))
				return (EXIT_FAILURE);
		if ((void *)(lc = lc + endian4(lc->cmdsize)) > (buf.st_size + ptr))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
