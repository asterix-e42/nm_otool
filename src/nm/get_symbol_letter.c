/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol_letter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:15:11 by tdumouli          #+#    #+#             */
/*   Updated: 2019/05/30 22:15:16 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nm_otool.h"

char		get_symbol_letter_32(struct nlist array)
{
	char		letter;

	if ((array.n_type & N_TYPE) == N_UNDF)
		letter = (array.n_value) ? 'C' : 'U';
	else if ((array.n_type & N_TYPE) == N_INDR)
		letter = 'I';
	else if ((array.n_type & N_TYPE) == N_ABS)
		letter = 'A';
	else if ((array.n_type & N_STAB))
		letter = '-';
	else if ((array.n_type & N_TYPE) == N_SECT)
	{
		letter = *(get_segment(0) + array.n_sect - 1);
		letter = (!letter) ? 'S' : letter;
	}
	else
		letter = '?';
	if (!(array.n_type & N_EXT) && letter != '?' && letter != '-')
		letter += 32;
	return (letter);
}

char		get_symbol_letter_64(struct nlist_64 array)
{
	char		letter;

	if ((array.n_type & N_TYPE) == N_UNDF)
		letter = (array.n_value) ? 'C' : 'U';
	else if ((array.n_type & N_TYPE) == N_INDR)
		letter = 'I';
	else if ((array.n_type & N_TYPE) == N_ABS)
		letter = 'A';
	else if ((array.n_type & N_STAB))
		letter = '-';
	else if ((array.n_type & N_TYPE) == N_SECT)
	{
		letter = *(get_segment(0) + array.n_sect - 1);
		letter = (!letter) ? 'S' : letter;
	}
	else
		letter = '?';
	if (!(array.n_type & N_EXT) && letter != '?' && letter != '-')
		letter += 32;
	return (letter);
}
