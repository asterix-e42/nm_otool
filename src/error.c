/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:16:09 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/12 15:32:31 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "libft.h"

int		handle_error(char *s)
{
	ft_putendl_fd(s, 2);
	return (EXIT_FAILURE);
}

int		handle_error_free(char *s)
{
	free(s);
	return (EXIT_FAILURE);
}

int		god(void *ptr, int reset)
{
	static void *ptr_end = NULL;

	if (reset)
		ptr_end = ptr;
	else
		return (ptr > ptr_end);
	return (EXIT_SUCCESS);
}
