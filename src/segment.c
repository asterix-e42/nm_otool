/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 02:19:19 by tdumouli          #+#    #+#             */
/*   Updated: 2019/04/27 01:47:50 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"
#include <unistd.h>
#include <stdlib.h>

void	putnb(unsigned long long *number, char *str, char is_64)
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
	struct section	*sec_tmp;
	int				i;
	int				j;
	int				merde;

	merde = get_number_segment(0);
	sec = (void *)segment + (sizeof(segment) + 1) * 8;
	i = -1;
	while (++i < (int)segment->nsects)
	{
		j = -1;
		sec_tmp = (void *)segment + (sizeof(segment) + 1) * 8;
		while (++j < i)
		{
			if (((sec_tmp->addr < sec->addr) && ((sec_tmp->addr + sec_tmp->size)
			> sec->addr)) || ((sec->addr < sec_tmp->addr)
			&& ((sec->addr + sec->size) > sec_tmp->addr)))
				handle_error("(sec contents at offset");
			sec_tmp++;
		}
		nmotool_part((void *)sec, i + merde, ptr, 8);
		sec++;
	}
	get_number_segment(i);
}

void	set_segment_64(struct segment_command_64 *segment, void *ptr)
{
	struct section_64	*sec;
	struct section_64	*sec_tmp;
	int					i;
	int					j;
	int					merde;

	merde = get_number_segment(0);
	sec = (void *)segment + (sizeof(segment) + 1) * 8;
	i = -1;
	while (++i < (int)segment->nsects)
	{
		j = -1;
		sec_tmp = (void *)segment + (sizeof(segment) + 1) * 8;
		while (++j < i)
		{
			if (((sec_tmp->addr < sec->addr) && ((sec_tmp->addr + sec_tmp->size)
			> sec->addr)) || ((sec->addr < sec_tmp->addr)
			&& ((sec->addr + sec->size) > sec_tmp->addr)))
				handle_error("(sec contents at offset");
			sec_tmp++;
		}
		nmotool_part((void *)sec, i + merde, ptr, 0);
		sec++;
	}
	get_number_segment(i);
}
