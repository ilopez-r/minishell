/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:29:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 17:30:58 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struct(t_data *data)
{
	data->line = NULL;
	data->path = NULL;
	data->ctnt = NULL;
	data->f = 0;
	data->d = 0;
	data->i = 0;
	data->j = 0;
	data->dup_stdin = dup(STDIN_FILENO);
}

int	input(t_data *d, char **env)
{
	if (check_quotes(d->line) == EXIT_FAILURE)
		return (printf("error: not closed quotes\n"), EXIT_SUCCESS);
	if (split_path(d) == 1)
		return (EXIT_SUCCESS);
	if (split_cmds(d) == 1)
		return (EXIT_SUCCESS);
	expand(d);
	if (parser (d, 0, 0) == 1)
		return (EXIT_SUCCESS);
	if (d->nodes == NULL)
		return (EXIT_SUCCESS);
	if (route (d, 0) == 1)
		return (EXIT_SUCCESS);
	if (executer(d, env, ((t_parser *)d->nodes->content), d->nodes) == 1)
		return (EXIT_SUCCESS);
	unlink("here_doc.tmp");
	return (EXIT_SUCCESS);
}

int	prompt(t_data *data)
{
	char	cur_dir[500];
	char	*dir;

	getcwd(cur_dir, sizeof(cur_dir));
	dir = ft_strjoin(cur_dir, " % ");
	if (!dir)
		return (EXIT_FAILURE);
	data->line = readline(dir);
	free (dir);
	dir = NULL;
	if (data->line == NULL)
	{
		printf ("exit\n");
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	minishell(t_data *data, char **env)
{
	while (69)
	{
		signal(SIGINT, signals);
		signal(SIGQUIT, SIG_IGN);
		if (prompt(data) == 1)
			exit (EXIT_FAILURE);
		if (ft_strncmp(data->line, "\0", 1) >= 1)
			add_history(data->line);
		if (input(data, env) == 1)
			return (EXIT_FAILURE);
		if (data->nodes != NULL)
			free_nodes(&data->nodes);
		if (data->cmds != NULL)
		{
			free_dptr(data->cmds);
			data->cmds = NULL;
		}
		if (data->line != NULL)
		{
			free(data->line);
			data->line = NULL;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		return (EXIT_FAILURE);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	init_struct(data);
	piti_shell();
	cigarrette();
	get_env (data, env, -1);
	if (minishell(data, env) == 1)
		return (free_all(data), EXIT_FAILURE);
	return (free_all(data), EXIT_SUCCESS);
}
