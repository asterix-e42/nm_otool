/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:15:44 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/03 12:19:49 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"

void	print_content(struct section_64 *s)
{
	ft_putstr("Contents of (");
	ft_putstr(s->segname);
	ft_putstr(",");
	ft_putstr(s->sectname);
	ft_putendl(") section");
}

int		print_otool_64(char *ptr, struct section_64 *section, struct stat buf)
{
	uint64_t	i;
	uint64_t	tmp[1];

	i = 0;
	if (endian4(section->size) > buf.st_size)
		return (EXIT_FAILURE);
	while (i < endian8(section->size))
	{
		if ((uint64_t)buf.st_size < (endian4(section->offset) + i))
			return (EXIT_FAILURE);
		if (!(i & 15))
		{
			*tmp = i + endian8(section->addr);
			putnb(tmp, "\t", 0);
		}
		ft_putchar_hex(*(ptr + endian4(section->offset) + i));
		ft_putchar(' ');
		i++;
		if (!(i & 15))
			ft_putchar('\n');
	}
	if ((i & 15))
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int		print_otool_32(char *ptr, struct section *section, struct stat buf)
{
	uint32_t	i;
	uint64_t	tmp[1];

	i = 0;
	if (endian4(section->size) > buf.st_size)
		return (EXIT_FAILURE);
	while (i < endian4(section->size))
	{
		if ((uint64_t)buf.st_size < (endian4(section->offset) + i) * 4)
			return (EXIT_FAILURE);
		if (!(i & 15))
		{
			*tmp = (uint64_t)(i + endian4(section->addr));
			putnb(tmp, "\t", 8);
		}
		ft_putchar_hex(*(ptr + endian4(section->offset) + i));
		ft_putchar(' ');
		i++;
		if (!(i & 15))
			ft_putchar('\n');
	}
	if ((i & 15))
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int		nmotool_part(struct section_64 *section, int is_64, char *ptr, void *b)
{
	if (!ft_strcmp(section->segname, "__TEXT")
			&& !ft_strcmp(section->sectname, "__text"))
	{
		print_content(section);
		if (!is_64)
			return (print_otool_64(ptr, section, *(struct stat *)b));
		else
			return (print_otool_32(ptr, (void *)section, *(struct stat *)b));
	}
	else if (!ft_strcmp(section->segname, "__BSS")
			&& !ft_strcmp(section->sectname, "__bss"))
		;
	else if (!ft_strcmp(section->segname, "__DATA")
			&& !ft_strcmp(section->sectname, "__data"))
		;
	return (EXIT_SUCCESS);
}

int		is_nm(void)
{
	return (0);
}
