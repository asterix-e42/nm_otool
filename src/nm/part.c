/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:15:33 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/10 14:29:51 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"

char	*get_segment(int reset)
{
	static char		*section_letter = NULL;

	if (!section_letter)
	{
		if (!(section_letter = malloc(sizeof(char) * MAX_SECT)))
			return (NULL);
		section_letter = ft_memset(section_letter, 0, MAX_SECT);
	}
	if (reset)
	{
		free(section_letter);
		section_letter = NULL;
	}
	return (section_letter);
}

int		nmotool_part(struct section_64 *section, int sect,
		char *ptr, void *is_64)
{
	char			*section_leter;

	(void)ptr;
	(void)is_64;
	section_leter = get_segment(0);
	if (!ft_strcmp(section->sectname, SECT_TEXT))
		section_leter[sect] = 'T';
	else if (!ft_strcmp(section->sectname, SECT_BSS))
		section_leter[sect] = 'B';
	else if (!ft_strcmp(section->sectname, SECT_DATA))
		section_leter[sect] = 'D';
	else
		section_leter[sect] = '\0';
	return (EXIT_SUCCESS);
}

int		is_nm(void)
{
	return (1);
}
