/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:16:23 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/12 01:11:17 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "libft.h"

int		main(int ac, char **av)
{
	int	ac_cpt;

	ac_cpt = 0;
	if (ac < 2)
		make_magic("./a.out", 0);
	else
		while (++ac_cpt < ac)
			make_magic(*(av + ac_cpt), ac);
	return (0);
}
