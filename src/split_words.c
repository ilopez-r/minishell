/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:16:53 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/21 16:55:18 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_words(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

static int	ft_counter_words(char const *s, char c)
{
	int		count;
	int		flag;
	char	quote;

	count = 0;
	flag = 0;
	while (*s != '\0')
	{
		quote = '\0';
		while ((*s == c || *s == '\'' || *s == '\"') && quote == '\0' && *s != '\0')
		{
			if (*s == '\'' || *s == '\"')
			{
				flag = !flag;
				quote = *s;
			}
			s++;
		}
		if (*s != '\0' && *s != quote && *s != ' ' && *s != '	')
			count++;
		if (flag)
		{
			while (*s != quote && *s != '\0')
				s++;
			flag = !flag;
		}
		while (*s != c && *s != '\0')
		{
			s++;
			if (*s == '\'' || *s == '\"')
				break ;
		}
	}
	return (count);
}

static int	ft_len_words(char const *s, char c, int *d)
{
	int		len;
	int		flag;
	char	quote;

	len = 0;
	flag = 0;
	quote = '\0';
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && quote == '\0' && s[*d] != '\0')
		{
			if (quote == '\0' || s[*d] == quote)
			{
				flag = !flag;
				quote = s[*d];
			}
			(*d)++;
			if (s[*d] == c || s[*d] == '\0')
				flag = !flag;
			if (flag && (s[*d] == c || s[*d] == '\0'))
				return ((*d)--, len);
			if (s[*d] == c)
			{
				(*d)++;
				quote = '\0';
			}
		}
		while ((flag || s[*d] != c) && s[*d] != quote && s[*d] != '\0')
		{
			len++;
			(*d)++;
			if (!flag && (s[*d] == '\'' || s[*d] == '\"'))
				return (len);
		}
		if (s[*d] == quote)
			return (len);
	}
	return (len);
}

char	**ft_split_words(char const *s, char c)
{
	char	**str;
	int		i;
	int		d;
	int		len;

	d = 0;
	i = -1;
	str = malloc((ft_counter_words (s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < ft_counter_words (s, c))
	{
		len = ft_len_words(s, c, &d);
		str[i] = ft_substr(s, (d - len), len);
		while (s[d] == c)
			d++;
		if (!(str[i]))
		{
			ft_free_words(str, i);
			return (0);
		}
	}
	str[i] = NULL;
	return (str);
}
