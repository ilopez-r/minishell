/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:16:53 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 15:11:58 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_words(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

static int	ft_counter_words(t_data *d, char const *s, char c, int count)
{
	while (*s != '\0')
	{
		d->q = '\0';
		while ((*s == c || *s == 39 || *s == 34) && d->q == '\0' && *s != '\0')
		{
			if (*s == '\'' || *s == '\"')
			{
				d->f = !d->f;
				d->q = *s;
			}
			s++;
		}
		if (*s != '\0' && *s != d->q && *s != ' ' && *s != '	')
			count++;
		if (d->f)
		{
			while (*s != d->q && *s != '\0')
				s++;
			d->f = !d->f;
		}
		while (*s != c && *s != '\0' && *(s)++)
			if (*s == '\'' || *s == '\"')
				break ;
	}
	return (count);
}

static int	ft_len_words(t_data *data, char const *s, char c, int *d)
{
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == 39 || s[*d] == 34) && data->q == '\0' && s[*d] != '\0')
		{
			if (data->q == '\0' || s[*d] == data->q)
			{
				data->f = !data->f;
				data->q = s[*d];
			}
			(*d)++;
			if (s[*d] == c || s[*d] == '\0')
				data->f = !data->f;
			if (data->f && (s[*d] == c || s[*d] == '\0'))
				return ((*d)--, data->len);
			if (s[*d] == c && (*d)++)
				data->q = '\0';
		}
		while ((data->f || s[*d] != c) && s[*d] != data->q && s[*d] != '\0'
			&& ++(*d) && ++data->len)
			if (!data->f && (s[*d] == '\'' || s[*d] == '\"'))
				return (data->len);
		if (s[*d] == data->q)
			return (data->len);
	}
	return (data->len);
}

char	**ft_split_words(t_data *data, char const *s, char c, int i)
{
	char	**str;
	int		len;
	int		count;

	data->d = 0;
	count = ft_counter_words (data, s, c, 0);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < count)
	{
		data->f = 0;
		data->q = '\0';
		data->len = 0;
		len = ft_len_words(data, s, c, &data->d);
		str[i] = ft_substr(s, (data->d - len), len);
		while (s[data->d] == c)
			data->d++;
		if (!(str[i]))
		{
			ft_free_words(str, i);
			return (0);
		}
	}
	str[i] = NULL;
	return (str);
}
