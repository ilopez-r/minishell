/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:35:15 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/15 15:07:41 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	split_cmds(t_data *d)
{
	d->cmds = ft_calloc(ft_counter (d->line, '|') + 1, sizeof(char **));
	if (!d->cmds)
		return (EXIT_FAILURE);
	d->cmds = ft_split (d->line, '|');
	if (!d->cmds)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
