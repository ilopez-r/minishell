/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:44:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/25 13:49:11 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*s;
	char	*t;

	s = (char *)str;
	i = ft_strlen(s);
	t = s + i;
	while (s <= t)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	return (0);
}
