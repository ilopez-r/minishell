/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:51:56 by ismael            #+#    #+#             */
/*   Updated: 2024/04/15 15:37:32 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_token_final_2(t_data *d, int *i, int *j, t_parser **n)
{
	if (d->f_hd == 0 && d->f_token == 1)
		(*n)->in = open(d->in, O_RDONLY);
	if (d->f_append == 0 && d->f_token == 2)
		(*n)->out = open(d->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->f_hd == 1 && d->f_token == 1)
		here_doc(d, n, NULL);
	if (d->f_append == 1 && d->f_token == 2)
		(*n)->out = open(d->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*n)->in == -1 || (*n)->out == -1)
		return (g_status = 1, printf("error: open infile or outfile\n"), 1);
	if (d->f_token == 1)
		free(d->in);
	if (d->f_token == 2)
		free(d->out);
	while (d->cmds[*i][*j] == ' ')
		(*j)++;
	return (EXIT_SUCCESS);
}

int	ft_token_final(t_data *d, int *i, int *j, t_parser **n)
{
	d->len = 0;
	d->a = 0;
	while (d->cmds[*i][*j] != ' ' && d->cmds[*i][*j] != '\0'
		&& ++(d->len) && ++(*j))
		if (d->cmds[*i][*j] == '<' || d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `newline'\n")
				, EXIT_FAILURE);
	if (d->f_token == 1)
		d->in = ft_calloc((d->len) + 1, sizeof(char));
	if (d->f_token == 2)
		d->out = ft_calloc((d->len) + 1, sizeof(char));
	d->len = (*j) - (d->len);
	while (d->cmds[*i][d->len] != ' ' && d->cmds[*i][d->len] != '\0')
	{
		if (d->f_token == 1)
			d->in[d->a] = d->cmds[*i][d->len];
		if (d->f_token == 2)
			d->out[d->a] = d->cmds[*i][d->len];
		(d->a)++;
		(d->len)++;
	}
	if (ft_token_final_2(d, i, j, n) == 1)
		return (free(d->in), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_token_continue(t_data *d, int *i, int *j)
{
	if (d->cmds[*i][*j] == '\0')
		return (printf ("syntax error near unexpected token `newline'\n"), 1);
	if (d->cmds[*i][*j] == '<')
		return (printf ("syntax error near unexpected token `<'\n"), 1);
	if (d->cmds[*i][*j] == '>')
		return (printf ("syntax error near unexpected token `>'\n"), 1);
	return (EXIT_SUCCESS);
}

int	ft_token_outfile(t_data *d, int *i, int *j, t_parser **n)
{
	d->f_append = 0;
	d->f_token = 2;
	if (d->cmds[*i][*j] == '>' && ++(*j))
	{
		if (d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n")
				, EXIT_FAILURE);
		if (d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (d->cmds[*i][*j] == '>' && ++(*j))
			d->f_append = 1;
		if (d->f_append == 1 && d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n")
				, EXIT_FAILURE);
		if (d->f_append == 1 && d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (d->f_append == 1 && d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>>'\n"), 1);
		while (d->cmds[*i][*j] == ' ' && ++(*j))
			if (ft_token_continue (d, i, j) == 1)
				return (EXIT_FAILURE);
		if (ft_token_final (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token_infile(t_data *d, int *i, int *j, t_parser **n)
{
	d->f_hd = 0;
	d->f_token = 1;
	if (d->cmds[*i][*j] == '<' && ++(*j))
	{
		if (d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n")
				, EXIT_FAILURE);
		if (d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		if (d->cmds[*i][*j] == '<' && ++(*j))
			d->f_hd = 1;
		if (d->f_hd == 1 && d->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n")
				, EXIT_FAILURE);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<<'\n"), 1);
		if (d->f_hd == 1 && d->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		while (d->cmds[*i][*j] == ' ' && ++(*j))
			if (ft_token_continue (d, i, j) == 1)
				return (EXIT_FAILURE);
		if (ft_token_final (d, i, j, n) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
