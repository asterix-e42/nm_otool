/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_ult.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:26:26 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/13 15:18:36 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"
#include <ar.h>
#include <mach-o/ranlib.h>

int8_t		is_arch(int is)
{
	static int8_t arch = 0;

	if (is)
		arch = !arch;
	return (arch);
}

static char	*archive_2(int32_t jmp, char *av, char *archive)
{
	char *aff;

	if (ft_strlen((archive + sizeof(struct ar_hdr))) > (size_t)jmp)
		return (NULL);
	if (!(aff = ft_memalloc(jmp + ft_strlen(av) + 16)))
		return (NULL);
	ft_strcpy(aff, av);
	ft_strcpy(aff + ft_strlen(av), "(");
	ft_strcpy(aff + ft_strlen(av) + 1, archive + sizeof(struct ar_hdr));
	*(aff + ft_strlen(av)
		+ ft_strlen((archive + sizeof(struct ar_hdr))) + 1) = ')';
	return (aff);
}

int			archive(void *ptr, struct stat buf, char *av)
{
	struct ar_hdr	*archive;
	int				jmp;
	int				i;
	char			*aff;

	aff = NULL;
	i = -1;
	archive = ptr + SARMAG;
	while (*(char *)archive && (++i >= 0))
	{
		jmp = ft_atoi(archive->ar_name + 3);
		if (ft_strncmp((char *)(archive + 1), SYMDEF, 9))
		{
			if (!(aff = archive_2(jmp, av, (void *)archive)))
				return (handle_error("name error"));
			if (magic(((char *)(archive + 1) + jmp), buf, aff, 3))
				return (handle_error_free(aff));
			free(aff);
		}
		if ((void *)(archive = (void *)archive + ft_atoi(archive->ar_size)
			+ sizeof(struct ar_hdr)) - ptr > buf.st_size)
			return (handle_error("error size no correct"));
	}
	return (EXIT_SUCCESS);
}
