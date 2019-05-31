/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mallocf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:20:40 by tdumouli          #+#    #+#             */
/*   Updated: 2019/05/31 16:26:11 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_mallocf(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit(EXIT_FAILURE);
	return (ret);
}
