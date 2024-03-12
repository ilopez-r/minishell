/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:25:57 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/01/15 11:30:05 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	gnl_ft_strchr(const char *str, int c)
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
			return (1);
		s++;
	}
	return (0);
}

void	*gnl_ft_calloc(size_t count, size_t size)
{
	char				*memory;
	unsigned int		i;

	memory = (char *)malloc(count * size);
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		memory[i] = '\0';
		i++;
	}
	return ((void *)memory);
}

void	*gnl_ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = (char *) dest;
	s = (const char *) src;
	if (!src && !dest)
	{
		return (0);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*s3;
	int		i;

	if (s1 == NULL)
	{
		s1 = ft_calloc(1, sizeof (char));
		if (!s1)
			return (free (s1), s1 = NULL, NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = len1 + len2;
	i = len1;
	s3 = malloc((len3 + 1) * sizeof(char));
	if (s3 == 0)
		return (free (s1), s1 = NULL, NULL);
	ft_memcpy(s3, s1, len1);
	ft_memcpy(&s3[i], s2, (len2 + 1));
	return (free (s1), s1 = NULL, s3);
}
