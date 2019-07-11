/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 02:19:19 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/11 19:39:58 by tdumouli         ###   ########.fr       */
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
	if (!(ret = ft_itoabase(n, "0123456789abcdef")))
		return ;
	write(1, "0000000000000000", 8 - ft_strlen(ret));
	ft_putstr(ret);
	ft_putstr(str);
	free(ret);
}

void	putnb(uint64_t *number, char *str, char is_64)
{
	char			*ret;

	if (!(ret = ft_itoabase(*number, "0123456789abcdef")))
		return ;
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

/*
** bug chelou aucune explication
*/

int		set_segment_32(struct segment_command *segment, void *ptr, void *b)
{
	struct section	*sec;
	int				i;
	int				merde;
	int				ret;

	ret = EXIT_SUCCESS;
	merde = get_number_segment(0);
	sec = (void *)segment + sizeof(*segment);
	i = -1;
	while (++i < (int)endian4(segment->nsects) && !ret)
	{
		if (i > 20)
			return (EXIT_FAILURE);
		if (is_nm())
			ret = nmotool_part((void *)sec, i + merde, ptr, NULL);
		else
			ret = nmotool_part((void *)sec, 8, ptr, b);
		sec++;
	}
	get_number_segment(i);
	return (ret);
}

int		set_segment_64(struct segment_command_64 *segment, void *ptr, void *b)
{
	struct section_64	*sec;
	int					i;
	int					merde;
	int					ret;

	ret = EXIT_SUCCESS;
	merde = get_number_segment(0);
	sec = (void *)segment + sizeof(*segment);
	i = -1;
	while (++i < (int)endian4(segment->nsects) && !ret)
	{
		if (i > 20)
			return (EXIT_FAILURE);
		if (is_nm())
			ret = nmotool_part((void *)sec, i + merde, ptr, NULL);
		else
			ret = nmotool_part((void *)sec, 0, ptr, b);
		sec++;
	}
	get_number_segment(i);
	return (ret);
}
