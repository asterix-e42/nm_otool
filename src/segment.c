/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 02:19:19 by tdumouli          #+#    #+#             */
/*   Updated: 2019/04/26 01:53:35 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"
#include <unistd.h>
#include <stdlib.h>


void putnb(unsigned long long *number, char *str, char _64)
{
	char *ret;

	ret = ft_itoabase(*number, "0123456789abcdef");
	write(1, "0000000000000000", 16 - _64 - ft_strlen(ret));
	ft_putstr(ret);
	ft_putstr(str);
	free(ret);
}

int get_number_segment(int n)
{
	static int number = 0;

	if (n == -1)
		number = 0;
	else
		number += n;
	return (number);
}

void set_segment_32(struct segment_command *segment, void *ptr)
{
	struct section *section;
	struct section *section_tmp;
	int i;
	int j;
	int merde;

	merde = get_number_segment(0);
	section = (void *)segment + (sizeof(segment) + 1) * 8;
	i = -1;
	while (++i < segment->nsects)
	{
		j = -1;
		section_tmp = (void *)segment + (sizeof(segment) + 1) * 8;
		while (++j < i)
		{
			if (((section_tmp->addr < section->addr)
				&& ((section_tmp->addr + section_tmp->size) > section->addr))
				|| ((section->addr < section_tmp->addr)
				&& ((section->addr + section->size) > section_tmp->addr)))
				handle_error("(section contents at offset");
			section_tmp++;
		}
		nmotool_part((void *)section, i + merde, ptr, 8);//one or one
		section++;
	}
	get_number_segment(i);
}

void set_segment_64(struct segment_command_64  *segment, void *ptr)
{
	struct section_64 *section;
	struct section_64 *section_tmp;
	int i;
	int j;
	int merde;

	merde = get_number_segment(0);
	section = (void *)segment + (sizeof(segment) + 1) * 8;
	i = -1;
	while (++i < segment->nsects)
	{
		j = -1;
		section_tmp = (void *)segment + (sizeof(segment) + 1) * 8;
		while (++j < i)
		{
			if (((section_tmp->addr < section->addr)
				&& ((section_tmp->addr + section_tmp->size) > section->addr))
				|| ((section->addr < section_tmp->addr)
				&& ((section->addr + section->size) > section_tmp->addr)))
				handle_error("(section contents at offset");
			section_tmp++;
		}
		nmotool_part((void *)section, i + merde, ptr, 0);//one or one
		section++;
	}
	get_number_segment(i);
}
