/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:41:19 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/27 15:39:20 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lon;
	char	*s2;

	lon = ft_strlen(s);
	if (s == 0)
		return (0);
	if (start > lon)
		return (ft_strdup(""));
	if (lon < len + start)
		len = lon - start;
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == 0)
		return (0);
	ft_memcpy(s2, s + start, len);
	s2[len] = '\0';
	return (s2);
}
