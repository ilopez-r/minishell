/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:51:21 by ismael            #+#    #+#             */
/*   Updated: 2024/04/15 16:30:45 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_f_d(t_parser *node)
{
	struct stat	file_info;
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (node->full_cmd[i] && ft_strchr(node->full_cmd[i], '-'))
		i++;
	if (node->full_cmd[i - 1])
	{
		while (node->full_cmd[i - 1][j])
		{
			if (ft_isdigit(node->full_cmd[i - 1][j]))
				g_status = 1;
			j++;
		}
	}
	if (stat(node->full_cmd[i], &file_info) == 0 || !node->full_cmd[i])
		return ;
	g_status = 1;
}

void	exec_route_child(t_data *data, t_parser *node, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data->f_hd == 1)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error("Here_doc read error\n");
		unlink("here_doc.tmp");
	}
	else if (node->in != 0)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error("Infile read error\n");
	}
	if (node->out != 1)
	{
		if (dup2(node->out, STDOUT_FILENO) == -1)
			msg_error("Wrt error\n");
	}
	g_status = execve(node->route, node->full_cmd, env);
}

void	exec_route_default(t_parser *node, char **env)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		g_status = 1;
		msg_error("Fork error\n");
	}
	if (pid == 0)
		g_status = execve(node->route, node->full_cmd, env);
	else
		waitpid(pid, NULL, 0);
	check_f_d(node);
}

void	exec_route(t_data *data, t_parser *node, char **env)
{
	pid_t		pid;
	t_list		*aux;

	if (builtins_executer (node, data) == 0)
		return ;
	else if (node->in == 0 && node->out == 1)
		exec_route_default (node, env);
	else
	{
		aux = data->nodes;
		node = ((t_parser *)aux->content);
		pid = fork();
		if (pid == -1)
		{
			g_status = 1;
			msg_error("Fork error\n");
		}
		if (pid == 0)
			exec_route_child (data, node, env);
		else
			waitpid(pid, NULL, 0);
		check_f_d(node);
	}
}
