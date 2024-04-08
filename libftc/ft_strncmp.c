/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:47:40 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/25 14:07:15 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			a;
	unsigned char	*st1;
	unsigned char	*st2;

	a = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while (st1[a] != '\0' && st2[a] != '\0' && (a < n - 1) && st1[a] == st2[a])
		a++;
	return (st1[a] - st2[a]);
}
