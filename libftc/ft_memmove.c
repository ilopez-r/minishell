/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:53:54 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/24 14:28:49 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dest;
	s = src;
	if (!src && !dest)
		return (0);
	if (s < d)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		ft_memcpy(d, s, n);
	}
	return (d);
}
