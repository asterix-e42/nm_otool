/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_ult.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:26:26 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/03 15:20:09 by tdumouli         ###   ########.fr       */
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

char	*archive_2(int32_t jmp, char *av, char *archive)
{
	char *aff;

	if (sizeof(struct ar_hdr) > (uint32_t)jmp)
	{
		handle_error("name too long, not correspond");
		return (NULL);
	}
	if (!(aff = ft_memalloc(jmp + ft_strlen(av) + 16)))
		return (NULL);
	ft_strcpy(aff, av);
	ft_strcpy(aff + ft_strlen(av), "(");
	ft_strcpy(aff + ft_strlen(av) + 1, archive + sizeof(struct ar_hdr) + 1);
	*(aff + ft_strlen(av)
		+ ft_strlen((archive + sizeof(struct ar_hdr))) + 0) = ')';
	return (aff);
}
