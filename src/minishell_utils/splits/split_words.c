/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:16:53 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/15 18:50:23 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	counter_continue(t_data *d, char const *s, char c, int *count)
{
	if (*s != '\0' && *s != d->q && *s != c)
		(*count)++;
}

static int	ft_counter_words(t_data *d, char const *s, char c, int count)
{
	while (*s != '\0')
	{
		d->q = '\0';
		while ((*s == c || *s == 39 || *s == 34) && *s != d->q && *s != '\0')
		{
			if (d->f == 0 && (*s == '\'' || *s == '\"'))
			{
				d->f = !d->f;
				d->q = *s;
			}
			if (++s && *s != '\0' && *s == d->q)
				break ;
		}
		counter_continue(d, s, c, &count);
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
		while ((s[*d] == '\'' || s[*d] == '\"') && s[(*d) + 1] == s[*d]
			&& ++(*d) && ++(*d))
			while (s[*d] == c)
				(*d)++;
		while ((s[*d] == 39 || s[*d] == 34) && data->q == '\0' && s[*d] != '\0')
		{
			if (data->q == '\0' || s[*d] == data->q)
			{
				data->f = !data->f;
				data->q = s[*d];
			}
			(*d)++;
			while (!data->f && s[*d] == c)
				(*d)++;
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

void	split_words_continue(t_data *data, char const *s, char c)
{
	if (s[data->d] != c)
	{
		if (s[data->d] == data->q && data->f == 1)
			data->d++;
		while (s[data->d] == c)
			data->d++;
	}
	while (s[data->d] == c)
		data->d++;
}

char	**ft_split_words(t_data *data, char const *s, char c, int i)
{
	char	**str;
	int		count;

	data->d = 0;
	data->f = 0;
	data->q = '\0';
	count = ft_counter_words (data, s, c, 0);
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (++i < count)
	{
		data->f = 0;
		data->q = '\0';
		data->len = 0;
		data->len = ft_len_words(data, s, c, &data->d);
		str[i] = ft_substr(s, (data->d - (data->len)), data->len);
		split_words_continue(data, s, c);
		if (!(str[i]))
		{
			free_dptr(str);
			return (0);
		}
	}
	return (str[i] = NULL, str);
}
