/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_ult.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:26:26 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/11 19:06:37 by tdumouli         ###   ########.fr       */
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

int8_t	is_arch(int is)
{
	static int8_t arch = 0;

	if (is)
		arch = !arch;
	return (arch);
}



char	*archive_2(int32_t jmp, char *av, char *archive)
{
	char *aff;

	if (!(aff = ft_memalloc(jmp + ft_strlen(av) + 16)))
		return (NULL);
	is_arch(1);
	ft_strcpy(aff, av);
	ft_strcpy(aff + ft_strlen(av), "(");
	ft_strcpy(aff + ft_strlen(av) + 1, archive + sizeof(struct ar_hdr));
	*(aff + ft_strlen(av)
		+ ft_strlen((archive + sizeof(struct ar_hdr))) + 1) = ')';
	return (aff);
}
