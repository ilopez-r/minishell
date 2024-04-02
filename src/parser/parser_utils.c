/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:51:56 by ismael            #+#    #+#             */
/*   Updated: 2024/04/02 22:31:54 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_final(t_data *d, int *i, int *j, t_parser **n)
{
	char		*in;
	char		*out;

	d->len = 0;
	d->a = 0;
	while (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '\0' && ++(d->len) && ++(*j))
		if (d->cmds[*i][*j] == '<' || d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
	d->len = (*j) - (d->len);
	if (d->f_token == 1)
		in = ft_calloc((d->len) + 1, sizeof(char));
	if (d->f_token == 2)
		out = ft_calloc((d->len) + 1, sizeof(char));
	while (d->cmds[*i][d->len] != ' ' && d->cmds[*i][d->len] != '\0')
	{
		if (d->f_token == 1)
			in[d->a] = d->cmds[*i][d->len];
		if (d->f_token == 2)
			out[d->a] = d->cmds[*i][d->len];
		(d->a)++;
		(d->len)++;
	}
	if (d->f_hd == 0 && d->f_token == 1)
		(*n)->in = open(in, O_RDONLY);
	if (d->f_hd == 0 && d->f_token == 2)
		(*n)->out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->f_hd == 1 && d->f_token == 1)//heredoc
		(*n)->in = open("h_d.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->f_hd == 1 && d->f_token == 2)
		(*n)->out = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*n)->in == -1 || (*n)->out == -1)
		return (ft_printf("syntax error open infile or outfile\n"), 1);
	while (d->cmds[*i][*j] == ' ')
		(*j)++;
	return (EXIT_SUCCESS);
}

int	ft_token_2(t_data *d, int *i, int *j, t_parser **n)
{
	d->f_hd = 0;
	d->f_token = 2;
	if (d->cmds[*i][*j] == '>' && ++(*j))
	{
		if (d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (d->cmds[*i][*j] == '>' && ++(*j))
			d->f_hd = 1;
		if (d->f_hd == 1 && d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>>'\n"), 1);
		while (d->cmds[*i][*j] == ' ' && ++(*j))
		{
			if (d->cmds[*i][*j] == '\0')
				return (printf ("syntax error near unexpected token `newline'\n"), 1);
			if (d->cmds[*i][*j] == '<')
				return (printf ("syntax error near unexpected token `<'\n"), 1);
			if (d->cmds[*i][*j] == '>')
				return (printf ("syntax error near unexpected token `>'\n"), 1);
		}
		if (ft_token_final (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token_1(t_data *d, int *i, int *j, t_parser **n)
{
	d->f_hd = 0;
	d->f_token = 1;
	if (d->cmds[*i][*j] == '<' && ++(*j))
	{
		if (d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		if (d->cmds[*i][*j] == '<' && ++(*j))
			d->f_hd = 1;
		if (d->f_hd == 1 && d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<<'\n"), 1);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		while (d->cmds[*i][*j] == ' ' && ++(*j))
		{
			if (d->cmds[*i][*j] == '\0')
				return (printf ("syntax error near unexpected token `newline'\n"), 1);
			if (d->cmds[*i][*j] == '<')
				return (printf ("syntax error near unexpected token `<'\n"), 1);
			if (d->cmds[*i][*j] == '>')
				return (printf ("syntax error near unexpected token `>'\n"), 1);
		}
		if (ft_token_final (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
