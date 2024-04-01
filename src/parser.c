/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:00 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/21 12:35:59 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parser_cmd(t_data *data)
{
	t_parser	*n;
	int			i;
	int			j;
	int			flag;
	int			len;
	int			h;
	int			w;
	int			b;
	char		*in;
	char		*out;
	char		*str;

	i = 0;
	while (data->cmds[i] != NULL)
	{
		j = 0;
		if (data->cmds[i][j] == '\0')
			return (printf ("Error: Only spaces\n"), EXIT_FAILURE);
		while (data->cmds[i][j] != '\0')
		{
			n = ft_calloc(1, sizeof(t_parser));
			n->outfile = 1;
			n->infile = 0;
			while (data->cmds[i][j] == ' ')
				j++;
			while (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
			{
				flag = 0;
				if (data->cmds[i][j] == '<')
				{
					j++;
					if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '|')
						return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '>')
						return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '<')
					{
						flag = 1;
						j++;
						if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '|')
							return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					}
					while (data->cmds[i][j] == ' ')
					{
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
					}
					len = 0;
					h = 0;
					while (data->cmds[i][j] != ' ' && data->cmds[i][j] != '\0')
					{
						len++;
						j++;
						if (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
					}
					in = ft_calloc(len + 1, sizeof(char));
					len = j - len;
					while (data->cmds[i][len] != ' ' && data->cmds[i][len] != '\0')
					{
						in[h] = data->cmds[i][len];
						h++;
						len++;
					}
					if (flag == 0)
						n->infile = open(in, O_RDONLY);
					if (flag == 1)
					{
						//crear here_doc
						n->infile = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					}
					if (n->infile == -1)
						return (ft_printf("Error: Open infile\n"), EXIT_FAILURE);
					while (data->cmds[i][j] == ' ')
						j++;
				}
				flag = 0;
				if (data->cmds[i][j] == '>')
				{
					j++;
					if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '|')
						return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '<')
						return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '>')
					{
						flag = 1;
						j++;
						if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '|')
							return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					}
					while (data->cmds[i][j] == ' ')
					{
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
					}
					len = 0;
					h = 0;
					while (data->cmds[i][j] != ' ' && data->cmds[i][len] != '\0')
					{
						len++;
						j++;
					}
					out = ft_calloc(len + 1, sizeof(char));
					len = j - len;
					while (data->cmds[i][len] != ' ' && data->cmds[i][len] != '\0')
					{
						out[h] = data->cmds[i][len];
						h++;
						len++;
					}
					if (flag == 0)
						n->outfile = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (flag == 1)
						n->outfile = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (n->infile == -1)
						return (ft_printf("Error: Open outfile\n"), EXIT_FAILURE);
					while (data->cmds[i][j] == ' ')
						j++;
				}
			}
			if (data->cmds[i][j] != ' ' && data->cmds[i][j] != '<'
				&& data->cmds[i][j] != '>' && data->cmds[i][j] != '\0')
			{
				len = 0;
				w = j;
				b = 0;
				while (data->cmds[i][j] != '<' && data->cmds[i][j] != '>'
					&& data->cmds[i][j] != '\0')
				{
					len++;
					j++;
				}
				str = ft_calloc (len + 1, sizeof(char));
				while (data->cmds[i][w] != '<' && data->cmds[i][w] != '>'
					&& data->cmds[i][w] != '\0')
				{
					str[b] = data->cmds[i][w];
					w++;
					b++;
				}
				n->full_cmd = ft_split_words(str, ' ');
			}
			while (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
			{
				flag = 0;
				if (data->cmds[i][j] == '<')
				{
					j++;
					if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '|')
						return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '>')
						return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '<')
					{
						flag = 1;
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '|')
							return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					}
					while (data->cmds[i][j] == ' ')
					{
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '\0')
							return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					}
					len = 0;
					h = 0;
					while (data->cmds[i][j] != ' ' && data->cmds[i][j] != '\0')
					{
						len++;
						j++;
						if (data->cmds[i][j] == '<' || data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					}
					in = ft_calloc(len + 1, sizeof(char));
					len = j - len;
					while (data->cmds[i][len] != ' ' && data->cmds[i][len] != '\0')
					{
						in[h] = data->cmds[i][len];
						h++;
						len++;
					}
					if (flag == 0)
						n->infile = open(in, O_RDONLY);
					if (flag == 1)
					{
						//crear here_doc
						n->infile = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					}
					if (n->infile == -1)
						return (ft_printf("Error: Open infile\n"), EXIT_FAILURE);
					while (data->cmds[i][j] == ' ')
						j++;
				}
				flag = 0;
				if (data->cmds[i][j] == '>')
				{
					j++;
					if (data->cmds[i][j] == '\0')
						return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '|')
						return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '<')
						return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
					if (data->cmds[i][j] == '>')
					{
						flag = 1;
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '|')
							return (printf ("syntax error near unexpected token `|'\n"), EXIT_FAILURE);
					}
					while (data->cmds[i][j] == ' ')
					{
						j++;
						if (data->cmds[i][j] == '<')
							return (printf ("syntax error near unexpected token `<'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '>')
							return (printf ("syntax error near unexpected token `>'\n"), EXIT_FAILURE);
						if (data->cmds[i][j] == '\0')
							return (printf ("syntax error near unexpected token `newline'\n"), EXIT_FAILURE);
					}
					len = 0;
					h = 0;
					while (data->cmds[i][j] != ' ' && data->cmds[i][j] != '\0')
					{
						len++;
						j++;
					}
					out = ft_calloc(len + 1, sizeof(char));
					len = j - len;
					while (data->cmds[i][len] != ' ' && data->cmds[i][len] != '\0')
					{
						out[h] = data->cmds[i][len];
						h++;
						len++;
					}
					if (flag == 0)
						n->outfile = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (flag == 1)
						n->outfile = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (n->infile == -1)
						return (ft_printf("Error: Open outfile\n"), EXIT_FAILURE);
					while (data->cmds[i][j] == ' ')
						j++;
				}
			}
			if (data->cmds[i][j] != '\0')
			{
				len = 0;
				h = 0;
				while (data->cmds[i][j] != ' ' && data->cmds[i][j] != '\0')
				{
					len++;
					j++;
				}
				in = ft_calloc(len + 1, sizeof(char));
				len = j - len;
				while (data->cmds[i][len] != ' ' && data->cmds[i][len] != '\0')
				{
					in[h] = data->cmds[i][len];
					h++;
					len++;
				}
				n->infile = open(in, O_RDONLY);
				if (n->infile == -1)
					return (printf ("Error: No such file or directory\n"), EXIT_FAILURE);
			}
		}
		ft_lstadd_back(&data->nodes, ft_lstnew(n));
		i++;
	}
	return (EXIT_SUCCESS);
}
