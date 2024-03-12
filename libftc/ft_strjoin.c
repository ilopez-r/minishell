/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:39:31 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/27 12:31:43 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*s3;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = len1 + len2;
	i = len1;
	s3 = malloc((len3 + 1) * sizeof(char));
	if (s3 == 0)
		return (0);
	ft_memcpy(s3, s1, len1);
	ft_memcpy(&s3[i], s2, (len2 + 1));
	return (s3);
}
