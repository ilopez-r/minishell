/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:21:55 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/25 16:25:24 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*i;

	s = (unsigned char *)str;
	i = s + n;
	while (s < i)
	{
		if (*s == (unsigned char)c)
			return (s);
		s++;
	}
	return (0);
}
