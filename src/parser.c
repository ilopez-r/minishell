/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:55:19 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 16:04:12 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_final(t_data *data, int *i, int *j, t_parser **n)
{
	int			len;
	int			a;
	char		*in;

	if (data->cmds[*i][*j] != '\0')
	{
		len = 0;
		a = 0;
		while (data->cmds[*i][*j] != ' ' && data->cmds[*i][*j] != '\0')
		{
			len++;
			j++;
		}
		in = ft_calloc(len + 1, sizeof(char));
		len = (*j) - len;
		while (data->cmds[*i][len] != ' ' && data->cmds[*i][len] != '\0')
		{
			in[a] = data->cmds[*i][len];
			a++;
			len++;
		}
		(*n)->in = open(in, O_RDONLY);
		if ((*n)->in == -1)
			return (printf ("Error: No such file or directory\n"), 1);
	}
	return (EXIT_SUCCESS);
}

int	ft_command(t_data *data, int *i, int *j, t_parser **n)
{
	int			len;
	int			a;
	int			b;
	char		*str;

	if (data->cmds[*i][*j] != ' ' && data->cmds[*i][*j] != '<'
		&& data->cmds[*i][*j] != '>' && data->cmds[*i][*j] != '\0')
	{
		len = 0;
		a = *j;
		b = 0;
		while (data->cmds[*i][*j] != '<' && data->cmds[*i][*j] != '>'
			&& data->cmds[*i][*j] != '\0')
		{
			len++;
			(*j)++;
		}
		str = ft_calloc (len + 1, sizeof(char));
		while (data->cmds[*i][a] != '<' && data->cmds[*i][a] != '>'
			&& data->cmds[*i][a] != '\0')
		{
			str[b] = data->cmds[*i][a];
			a++;
			b++;
		}
		(*n)->full_cmd = ft_split_words(data, str, ' ', -1);
		if (!(*n)->full_cmd)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token_continue(t_data *data, int *i, int *j, int *flag, t_parser **n, int *flag2)
{
	int			len;
	int			a;
	char		*in;
	char		*out;

	len = 0;
	a = 0;
	while (data->cmds[*i][*j] != ' ' && data->cmds[*i][*j] != '\0' && ++len && ++(*j))
		if (data->cmds[*i][*j] == '<' || data->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
	len = (*j) - len;
	if (*flag2 == 0)
		in = ft_calloc(len + 1, sizeof(char));
	if (*flag2 == 1)
		out = ft_calloc(len + 1, sizeof(char));
	while (data->cmds[*i][len] != ' ' && data->cmds[*i][len] != '\0')
	{
		if (*flag2 == 0)
			in[a] = data->cmds[*i][len];
		if (*flag2 == 1)
			out[a] = data->cmds[*i][len];
		a++;
		len++;
	}
	if (*flag == 0 && *flag2 == 0)
		(*n)->in = open(in, O_RDONLY);
	if (*flag == 0 && *flag2 == 1)
		(*n)->out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*flag == 1 && *flag2 == 0)//heredoc
		(*n)->in = open("h_d.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*flag == 1 && *flag2 == 1)
		(*n)->out = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*n)->in == -1 || (*n)->out == -1)
		return (ft_printf("syntax error open infile or outfile\n"), 1);
	while (data->cmds[*i][*j] == ' ')
		(*j)++;
	return (EXIT_SUCCESS);
}

int	ft_token_2(t_data *data, int *i, int *j, t_parser **n)
{
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 1;
	if (data->cmds[*i][*j] == '>' && ++(*j))
	{
		if (data->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (data->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (data->cmds[*i][*j] == '>' && ++(*j))
			flag = 1;
		if (flag == 1 && data->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (flag == 1 && data->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<'\n"), 1);
		if (flag == 1 && data->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>>'\n"), 1);
		while (data->cmds[*i][*j] == ' ' && ++(*j))
		{
			if (data->cmds[*i][*j] == '\0')
				return (printf ("syntax error near unexpected token `newline'\n"), 1);
			if (data->cmds[*i][*j] == '<')
				return (printf ("syntax error near unexpected token `<'\n"), 1);
			if (data->cmds[*i][*j] == '>')
				return (printf ("syntax error near unexpected token `>'\n"), 1);
		}
		if (ft_token_continue (data, i, j, &flag, n, &flag2) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_token_1(t_data *data, int *i, int *j, t_parser **n)
{
	int	flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	if (data->cmds[*i][*j] == '<' && ++(*j))
	{
		if (data->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (data->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		if (data->cmds[*i][*j] == '<' && ++(*j))
			flag = 1;
		if (flag == 1 && data->cmds[*i][*j] == '\0')
			return (printf ("syntax error near unexpected token `newline'\n"), 1);
		if (flag == 1 && data->cmds[*i][*j] == '<')
			return (printf ("syntax error near unexpected token `<<'\n"), 1);
		if (flag == 1 && data->cmds[*i][*j] == '>')
			return (printf ("syntax error near unexpected token `>'\n"), 1);
		while (data->cmds[*i][*j] == ' ' && ++(*j))
		{
			if (data->cmds[*i][*j] == '\0')
				return (printf ("syntax error near unexpected token `newline'\n"), 1);
			if (data->cmds[*i][*j] == '<')
				return (printf ("syntax error near unexpected token `<'\n"), 1);
			if (data->cmds[*i][*j] == '>')
				return (printf ("syntax error near unexpected token `>'\n"), 1);
		}
		if (ft_token_continue (data, i, j, &flag, n, &flag2) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_cmd(t_data *data, int i, int j)
{
	t_parser	*n;

	while (data->cmds[i] != NULL)
	{
		j = 0;
		if (data->cmds[i][j] == '\0')
			return (printf ("syntax error only spaces\n"), EXIT_FAILURE);
		while (data->cmds[i][j] != '\0')
		{
			n = ft_calloc(1, sizeof(t_parser));
			n->out = 1;
			n->in = 0;
			while (data->cmds[i][j] == ' ')
				j++;
			while (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
			{
				if (ft_token_1 (data, &i, &j, &n) == 1)
					return (EXIT_FAILURE);
				if (ft_token_2 (data, &i, &j, &n) == 1)
					return (EXIT_FAILURE);
			}
			if (ft_command (data, &i, &j, &n) == 1)
				return (EXIT_FAILURE);
			while (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
			{
				if (ft_token_1 (data, &i, &j, &n) == 1)
					return (EXIT_FAILURE);
				if (ft_token_2 (data, &i, &j, &n) == 1)
					return (EXIT_FAILURE);
			}
			ft_parser_final (data, &i, &j, &n);
		}
		ft_lstadd_back(&data->nodes, ft_lstnew(n));
		i++;
	}
	return (EXIT_SUCCESS);
}
