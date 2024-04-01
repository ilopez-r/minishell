/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:29:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/01 13:12:20 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}atexit(ft_leaks); */

static void	init_struct(t_data *data)
{
	data->line = NULL;
	data->path = NULL;
}

int	check_quotes(char *s)
{
	int		i;
	int		fq_simple;
	int		fq_double;

	i = 0;
	fq_simple = 0;
	fq_double = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[i] == '\"' && !fq_simple)
			fq_double = !fq_double;
		i++;
	}
	if (fq_double || fq_simple)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	input(t_data *d)
{
	if (check_quotes(d->line) == EXIT_FAILURE)
		return (printf("Error: not closed quotes\n"), EXIT_SUCCESS);
	split_path(d);
	if (split_cmds(d) == 1)
		return (EXIT_SUCCESS);
	/*int	i;
	i = 0;
	while (d->cmds[i] != NULL)
	{
		printf("%s\n", d->cmds[i]);
		i++;
	}*/
	if (parser_cmd (d) == 1)
		return (EXIT_SUCCESS);
	/*t_list	*aux;
	int		i;

	aux = d->nodes;
	while (aux)
	{
		i = 0;
		//printf("full_path:%s\n", ((t_parser *)(aux->content))->route);
		if (((t_parser *)(aux->content))->full_cmd)
		{
			while (((t_parser *)(aux->content))->full_cmd[i])
			{
				printf("cmd %i:%s\n", i,
					((t_parser *)(aux->content))->full_cmd[i]);
				i++;
			}
		}
		printf("Outfile: %d\nInfile: %d\n\n",
			((t_parser *)(aux->content))->outfile,
			((t_parser *)(aux->content))->infile);
		aux = aux->next;
	}*/
	/*int i = -1;
	while (d->subsplit[++i])
		printf("d->subsplit[%d] = %s\n", i, d->subsplit[i]);*/
	return (EXIT_SUCCESS);
}

int	minishell(t_data *data, char **env)
{
	piti_shell();
	cigarrette();
	get_env (data, env);
	while (69)
	{
		//hacer minitalk;
		if (prompt(data) == 1)
			exit(EXIT_FAILURE);
		if (ft_strncmp(data->line, "\0", 1) >= 1)
			add_history(data->line);
		if (input(data) == 1)
			return (EXIT_FAILURE);
		free_nodes(&data->nodes);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		exit (EXIT_FAILURE);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit (EXIT_FAILURE);
	init_struct(data);
	if (minishell(data, env) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
