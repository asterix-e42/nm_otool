/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:12:14 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/03 13:56:39 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft.h"
#include <math.h>
#include <stdlib.h>

char	*ft_itoabase(unsigned long long int nb, char *b2)
{
	char				*ret;
	unsigned long int	tmp;
	size_t				size;
	int					skt;
	unsigned int		max;

	if (!b2 && !*b2 && !*(b2 + 1))
		return (0);
	tmp = nb;
	skt = 0;
	max = ft_strlen(b2);
	size = 1;
	while (tmp /= max)
		++size;
	if (!(ret = (char *)malloc(sizeof(char) * (size + 4))))
		return (NULL);
	*(ret + size) = '\0';
	while (--size + 1)
	{
		*(ret + size) = *(b2 + (nb % max));
		nb /= max;
	}
	return (ret);
}
