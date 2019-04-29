/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 02:19:19 by tdumouli          #+#    #+#             */
/*   Updated: 2019/04/29 23:36:39 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"
#include <unistd.h>
#include <stdlib.h>

void	putnb_32(uint32_t *number, char *str)
{
	char			*ret;
	uint64_t		n;

	n = 0 + *number;
	ret = ft_itoabase(n, "0123456789abcdef");
	write(1, "0000000000000000", 8 - ft_strlen(ret));
	ft_putstr(ret);
	ft_putstr(str);
	free(ret);
}

void	putnb(uint64_t *number, char *str, char is_64)
{
	char			*ret;

	ret = ft_itoabase(*number, "0123456789abcdef");
	write(1, "0000000000000000", 16 - is_64 - ft_strlen(ret));
	ft_putstr(ret);
	ft_putstr(str);
	free(ret);
}

int		get_number_segment(int n)
{
	static int		number = 0;

	if (n == -1)
		number = 0;
	else
		number += n;
	return (number);
}

void	set_segment_32(struct segment_command *segment, void *ptr)
{
	struct section	*sec;
	struct section	*tmp;
	int				i;
	int				j;
	int				merde;

	merde = get_number_segment(0);
	sec = (void *)segment + sizeof(*segment);
	i = -1;
	while (++i < (int)endian4(segment->nsects))
	{
		j = -1;
		tmp = (void *)segment + (sizeof(segment) + 1) * 8;
		while (++j < i
				&& ++tmp)
			if (((endian4(tmp->addr) < endian4(sec->addr))
	&& ((endian4(tmp->addr) + endian4(tmp->size))
	> endian4(sec->addr))) || ((endian4(sec->addr) < endian4(tmp->addr))
	&& ((endian4(sec->addr) + endian4(sec->size)) > endian4(tmp->addr))))
				handle_error("contents at offset");
		nmotool_part((void *)sec, i + merde, ptr, 8);
		sec++;
	}
	get_number_segment(i);
}

void	set_segment_64(struct segment_command_64 *segment, void *ptr)
{
	struct section_64	*sec;
	struct section_64	*tmp;
	int					i;
	int					j;
	int					merde;

	merde = get_number_segment(0);
	sec = (void *)segment + sizeof(*segment);
	i = -1;
	while (++i < (int)endian4(segment->nsects))
	{
		j = -1;
		tmp = (void *)segment + (sizeof(segment)) * 8;
		while (++j < i
				&& ++tmp)
			if (((endian8(tmp->addr) < endian8(sec->addr))
	&& ((endian8(tmp->addr) + endian8(tmp->size))
	> endian8(sec->addr))) || ((endian8(sec->addr) < endian8(tmp->addr))
	&& ((endian8(sec->addr) + endian8(sec->size)) > endian8(tmp->addr))))
				handle_error("(sec contents at offset");
		nmotool_part((void *)sec, i + merde, ptr, 0);
		sec++;
	}
	get_number_segment(i);
}
