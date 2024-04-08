/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:51:38 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/02/22 16:31:25 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_free(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

static int	ft_counter(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (i);
}

static int	ft_len(char const *s, char c, int d)
{
	int	len;

	len = 0;
	while (s[d] != '\0' && s[d] != c)
	{
		len++;
		d++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		d;

	d = 0;
	i = -1;
	str = malloc((ft_counter (s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < ft_counter (s, c))
	{
		while (s[d] == c)
			d++;
		str[i] = ft_substr(s, d, ft_len(s, c, d));
		if (!(str[i]))
		{
			ft_free(str, i);
			return (0);
		}
		d = d + ft_len(s, c, d);
	}
	str[i] = 0;
	return (str);
}
