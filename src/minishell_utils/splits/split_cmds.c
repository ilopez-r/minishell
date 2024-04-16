/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:35:15 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 13:14:47 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	counter_continue(char const **s, char c, char *quote)
{
	if (**s == c)
		return (printf ("syntax error near unexpected token `|'\n"), -2);
	while (**s != c && **s != '\0')
	{
		if ((**s == '<' || **s == '>') && (*s)++)
		{
			while (**s == ' ')
				(*s)++;
			if (**s == c)
				return (printf ("s error near unexpected token `|'\n"), -2);
		}
		if (**s == '\'' || **s == '\"')
		{
			*quote = **s;
			(*s)++;
			while (**s != *quote)
				(*s)++;
		}
		(*s)++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_counter_cmds(char const *s, char c, int i)
{
	char	quote;

	while (*s != '\0')
	{
		if (counter_continue(&s, c, &quote) == -2)
			return (-2);
		if (*s == c && s++)
		{
			while (*s == ' ')
				s++;
			if (*s == c || *s == '\0')
				return (printf ("syntax error pipes are wrong\n"), -2);
		}
		i++;
	}
	return (i);
}

static int	ft_len_cmds(char const *s, char c, int d)
{
	int		len;
	char	quote;

	len = 0;
	while (s[d] != '\0' && s[d] != c)
	{
		if (s[d] == '\'' || s[d] == '\"')
		{
			quote = s[d];
			d++;
			len++;
			while (s[d] != quote)
			{
				d++;
				len++;
			}
		}
		len++;
		d++;
	}
	return (len);
}

char	**ft_split_cmds(char const *s, char c)
{
	char	**str;
	int		i;
	int		d;

	d = 0;
	i = -1;
	str = malloc((ft_counter_cmds (s, c, 0) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < ft_counter_cmds (s, c, 0))
	{
		while (s[d] == c)
			d++;
		while (s[d] == ' ')
			d++;
		str[i] = ft_substr(s, d, ft_len_cmds(s, c, d));
		if (!(str[i]))
		{
			free_dptr(str);
			return (0);
		}
		d = d + ft_len_cmds(s, c, d);
	}
	str[i] = 0;
	return (str);
}

int	split_cmds(t_data *d)
{
	int	i;

	i = 0;
	while (d->line[i] == ' ' || d->line[i] == '	')
		i++;
	if (d->line[i] == '\0')
		return (EXIT_FAILURE);
	d->cmds = ft_split_cmds (d->line, '|');
	if (d->cmds == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
