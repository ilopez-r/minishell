/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:16:53 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/06 12:27:09 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

/*static int	ft_len_words(t_data *data, char const *s, char c, int *d)
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
			while (s[*d] == data->q && data->f == 1 && (s[(*d) + 1] == '\'' || s[(*d) + 1] == '\"' || s[(*d) + 1] == ' '))
			{
				(*d)++;
				while (s[*d] == ' ')
					(*d)++;
				if (s[*d] == data->q && s[*d] == s[(*d) + 1])
					(*d)++;
				if (s[(*d) + 1] != data->q)
				{
					(*d)++;
					data->f = !data->f;
					data->q = '\0';
					break ;
				}
				while ((s[*d] == '\'' || s[*d] == '\"') && (s[(*d) + 1] == '\'' || s[(*d) + 1] == '\"'))
				{
					(*d)++;
					if (s[*d] == s[(*d) - 1] && (s[(*d) + 1] == '\'' || s[(*d) + 1] == '\"'))
						(*d)++;
				}
				data->f = !data->f;
				data->q = '\0';
			}
			if (s[*d] == c || s[*d] == '\0')
				data->f = !data->f;
			if (data->f && (s[*d] == c || s[*d] == '\0'))
				return ((*d)--, data->len);
			if (s[*d] == c && (*d)++)
				data->q = '\0';
			if (s[*d] != data->q && s[(*d) + 1] != '\'' && s[(*d) + 1] != '\"')
			{
				data->f = !data->f;
				data->q = '\0';
			}
		}
		while ((data->f || s[*d] != c) && s[*d] != data->q && s[*d] != '\0'
			&& ++(*d) && ++data->len)
			if (!data->f && (s[*d] == '\'' || s[*d] == '\"'))
				return (data->len);
		if (s[*d] == data->q)
			return (data->len);
	}
	return (data->len);
}*/

static int	ft_len_words(t_data *data, char const *s, char c, int *d)
{
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && s[(*d) + 1] == s[*d])
		{
			(*d)++;
			(*d)++;
		}
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
/*static int	ft_len_words(t_data *data, char const *s, char c, int *d)
{
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && s[(*d) + 1] == s[*d])
		{
			(*d)++;
			(*d)++;
		}
		while ((s[*d] == 39 || s[*d] == 34) && data->q == '\0' && s[*d] != '\0')
		{
			if (data->q == '\0' || s[*d] == data->q)
			{
				data->f = !data->f;
				data->q = s[*d];
			}
			(*d)++;
			while (s[*d] != data->q)
			{
				(*d)++;
				data->len++;
			}
			if (data->f && s[*d] == data->q)
			{
				data->f = 0;
				data->q = '\0';
				return (data->len);
			}
			//if (s[*d] == c || s[*d] == '\0')
			//	data->f = !data->f;
			//if (data->f && (s[*d] == c || s[*d] == '\0'))
			//	return ((*d)--, data->len);
			//if (s[*d] == c && (*d)++)
			//	data->q = '\0';
		}
		while ((data->f || s[*d] != c) && s[*d] != data->q && s[*d] != '\0'
			&& ++(*d) && ++data->len)
			if (!data->f && (s[*d] == '\'' || s[*d] == '\"'))
				return (data->len);
		if (s[*d] == data->q)
			return (data->len);
	}
	return (data->len);
}*/

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
		if (s[data->d] != c)
		{
			if (s[data->d] == data->q && data->f == 1)
				data->d++;
			while (s[data->d] == c)
				data->d++;
		}
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
