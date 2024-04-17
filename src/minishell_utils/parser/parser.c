/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:55:19 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 18:23:21 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parser_final(t_data *d, int *i, int *j, t_parser **n)
{
	while (d->cmds[*i][*j] != '\0')
	{
		d->len = 0;
		d->a = -1;
		while (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '\0' && ++(d->len))
			(*j)++;
		d->in = ft_calloc(d->len + 1, sizeof(char));
		d->len = (*j) - d->len;
		while (d->cmds[*i][d->len] != ' ' && d->cmds[*i][d->len] != '\0')
		{
			d->in[++(d->a)] = d->cmds[*i][d->len];
			(d->len)++;
		}
		if (((*n)->in != 0))
			close((*n)->in);
		(*n)->in = open(d->in, O_RDONLY);
		free(d->in);
		if ((*n)->in == -1)
			return (close((*n)->in),
				printf ("error: no such file or directory\n"), 1);
		while (d->cmds[*i][*j] == ' ')
			(*j)++;
	}
	return (EXIT_SUCCESS);
}

int	ft_command_continue(t_data *d, int *i, t_parser **n)
{
	d->b = 0;
	d->str = ft_calloc ((d->len) + 1, sizeof(char));
	while (d->cmds[*i][d->a] != '<' && d->cmds[*i][d->a] != '>'
		&& d->cmds[*i][d->a] != '\0')
	{
		if (d->cmds[*i][d->a] == d->q)
		{
			d->str[d->b] = d->cmds[*i][d->a];
			(d->a)++;
			(d->b)++;
			while (d->cmds[*i][d->a] != d->q)
			{
				d->str[d->b] = d->cmds[*i][d->a];
				(d->a)++;
				(d->b)++;
			}
		}
		d->str[d->b] = d->cmds[*i][d->a];
		(d->a)++;
		(d->b)++;
	}
	(*n)->full_cmd = ft_split_words(d, d->str, ' ', -1);
	if (!(*n)->full_cmd)
		return (free(d->str), d->str = NULL, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_command(t_data *d, int *i, int *j, t_parser **n)
{
	if (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '<'
		&& d->cmds[*i][*j] != '>' && d->cmds[*i][*j] != '\0')
	{
		d->len = 0;
		d->a = *j;
		while (d->cmds[*i][*j] != '<' && d->cmds[*i][*j] != '>'
			&& d->cmds[*i][*j] != '\0')
		{
			if (d->cmds[*i][*j] == '\'' || d->cmds[*i][*j] == '\"')
			{
				d->q = d->cmds[*i][*j];
				(d->len)++;
				while (d->cmds[*i][++(*j)] != d->q)
					(d->len)++;
			}
			(d->len)++;
			(*j)++;
		}
		if (ft_command_continue (d, i, n) == 1)
			return (EXIT_FAILURE);
	}
	return (free(d->str), d->str = NULL, EXIT_SUCCESS);
}

int	ft_token(t_data *d, int *i, int *j, t_parser **n)
{
	while (d->cmds[*i][*j] == '<' || d->cmds[*i][*j] == '>')
	{
		if ((*n)->in != 0 && d->cmds[*i][*j] == '<')
			close((*n)->in);
		if ((*n)->out != 1 && d->cmds[*i][*j] == '>')
			close((*n)->out);
		if (ft_token_infile (d, i, j, n) == 1)
			return (EXIT_FAILURE);
		if (ft_token_outfile (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	d->len = 0;
	d->a = -1;
	return (EXIT_SUCCESS);
}

int	parser(t_data *d, int i, int j)
{
	while (d->cmds[i] != NULL)
	{
		j = 0;
		if (d->cmds[i][j] == '\0')
			return (EXIT_FAILURE);
		while (d->cmds[i][j] != '\0')
		{
			d->n = ft_calloc(1, sizeof(t_parser));
			d->n->out = 1;
			d->n->in = 0;
			while (d->cmds[i][j] == ' ')
				j++;
			if (ft_token (d, &i, &j, &d->n) == 1)
				return (free_t_parser(d->n), EXIT_FAILURE);
			if (ft_command (d, &i, &j, &d->n) == 1)
				return (free_t_parser(d->n), EXIT_FAILURE);
			if (ft_token (d, &i, &j, &d->n) == 1)
				return (free_t_parser(d->n), EXIT_FAILURE);
			if (ft_parser_final (d, &i, &j, &d->n) == 1)
				return (free_t_parser(d->n), EXIT_FAILURE);
		}
		ft_lstadd_back(&d->nodes, ft_lstnew(d->n));
		i++;
	}
	return (EXIT_SUCCESS);
}
