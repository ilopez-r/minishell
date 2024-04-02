/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:55:19 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 22:33:08 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser_final(t_data *d, int *i, int *j, t_parser **n)
{
	char		*in;

	if (d->cmds[*i][*j] != '\0')
	{
		d->len = 0;
		d->a = -1;
		while (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '\0')
		{
			(d->len)++;
			(*j)++;
		}
		in = ft_calloc(d->len + 1, sizeof(char));
		d->len = (*j) - d->len;
		while (d->cmds[*i][d->len] != ' ' && d->cmds[*i][d->len] != '\0')
		{
			in[(d->a)++] = d->cmds[*i][d->len];
			(d->len)++;
		}
		(*n)->in = open(in, O_RDONLY);
		if ((*n)->in == -1)
			return (printf ("Error: No such file or directory\n"), 1);
	}
	return (EXIT_SUCCESS);
}

int	ft_command(t_data *d, int *i, int *j, t_parser **n)
{
	if (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '<'
		&& d->cmds[*i][*j] != '>' && d->cmds[*i][*j] != '\0')
	{
		d->len = 0;
		d->a = *j;
		d->b = 0;
		while (d->cmds[*i][*j] != '<' && d->cmds[*i][*j] != '>'
			&& d->cmds[*i][*j] != '\0')
		{
			(d->len)++;
			(*j)++;
		}
		d->str = ft_calloc ((d->len) + 1, sizeof(char));
		while (d->cmds[*i][d->a] != '<' && d->cmds[*i][d->a] != '>'
			&& d->cmds[*i][d->a] != '\0')
		{
			d->str[d->b] = d->cmds[*i][d->a];
			(d->a)++;
			(d->b)++;
		}
		(*n)->full_cmd = ft_split_words(d, d->str, ' ', -1);
		if (!(*n)->full_cmd)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token(t_data *d, int *i, int *j, t_parser **n)
{
	while (d->cmds[*i][*j] == '<' || d->cmds[*i][*j] == '>')
	{
		if (ft_token_1 (d, i, j, n) == 1)
			return (EXIT_FAILURE);
		if (ft_token_2 (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_data *d, int i, int j)
{
	t_parser	*n;

	while (d->cmds[i] != NULL)
	{
		j = 0;
		if (d->cmds[i][j] == '\0')
			return (printf ("syntax error only spaces\n"), EXIT_FAILURE);
		while (d->cmds[i][j] != '\0')
		{
			n = ft_calloc(1, sizeof(t_parser));
			n->out = 1;
			n->in = 0;
			while (d->cmds[i][j] == ' ')
				j++;
			if (ft_token (d, &i, &j, &n) == 1)
				return (EXIT_FAILURE);
			if (ft_command (d, &i, &j, &n) == 1)
				return (EXIT_FAILURE);
			if (ft_token (d, &i, &j, &n) == 1)
				return (EXIT_FAILURE);
			if (ft_parser_final (d, &i, &j, &n) == 1)
				return (EXIT_FAILURE);
		}
		ft_lstadd_back(&d->nodes, ft_lstnew(n));
		i++;
	}
	return (EXIT_SUCCESS);
}
