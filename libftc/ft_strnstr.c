/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:01:16 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/01/30 12:46:57 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s;
	char	*c;
	size_t	i;
	size_t	a;

	s = (char *)haystack;
	c = (char *)needle;
	i = 0;
	if (*c == '\0')
		return (s);
	while (s[i] != '\0' && i < len)
	{
		a = 0;
		while (s[i + a] == c[a] && (i + a) < len)
		{
			if (c[a + 1] == '\0')
				return (&s[i]);
			a++;
		}
		i++;
	}
	return (0);
}
