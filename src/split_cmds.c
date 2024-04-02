/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:35:15 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 12:01:23 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_cmds(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

static int	ft_counter_cmds(char const *s, char c, int i)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (printf ("syntax error near unexpected token `|'\n"), -1);
		while (*s != c && *s != '\0')
		{
			if ((*s == '<' || *s == '>') && *(s)++)
			{
				while (*s == ' ')
					s++;
				if (*s == c)
					return (printf ("s error near unexpected token `|'\n"), -1);
			}
			s++;
		}
		if (*s == c && *(s)++)
		{
			while (*s == ' ')
				s++;
			if (*s == c || *s == '\0')
				return (printf ("syntax error pipes are wrong\n"), -1);
		}
		i++;
	}
	return (i);
}

static int	ft_len_cmds(char const *s, char c, int d)
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
			ft_free_cmds(str, i);
			return (0);
		}
		d = d + ft_len_cmds(s, c, d);
	}
	str[i] = 0;
	return (str);
}

int	split_cmds(t_data *d)
{
	int	count;

	count = ft_counter_cmds (d->line, '|', 0);
	if (count == -1)
		return (EXIT_FAILURE);
	d->cmds = ft_calloc(count + 1, sizeof(char **));
	if (!d->cmds)
		return (EXIT_FAILURE);
	d->cmds = ft_split_cmds (d->line, '|');
	if (!d->cmds)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
