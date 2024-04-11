/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:51:21 by ismael            #+#    #+#             */
/*   Updated: 2024/04/10 17:39:56 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	msg_error(char *str)
{
	unlink("here_doc.tmp");
	// si no funciona, probar: data->f_hd = 0;
	perror(str);
	exit(EXIT_FAILURE);
}

void	exec_route_child(t_data *data, t_parser *node, char **env)
{
	//minitalk;
	if (data->f_hd == 1)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error("Here_doc read error\n");
		unlink("here_doc.tmp");
		// si no funciona, probar: data->f_hd = 0;
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
	//g_status = execve(node->route, node->full_cmd, env);
	//sustituir lo de abajo por g_status
	if (execve(node->route, node->full_cmd, env) == -1)
		msg_error("Exec error\n");
}

void	exec_route(t_data *data, t_parser *node, char **env)
{
	pid_t		pid;
	t_list		*aux;

	if (builtins_executer (node, data) == 0)
		return ;
	else if (node->in == 0 && node->out == 1)
	{
		pid = fork();
		if (pid == -1)
		{
			//g_status = 1;
			msg_error("Fork error\n");
		}
		if (pid == 0)
		{
			if (execve(node->route, node->full_cmd, env) == -1)
				msg_error("Exec error\n");
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
	{
		aux = data->nodes;
		node = ((t_parser *)aux->content);
		pid = fork();
		if (pid == -1)
		{
			//g_status = 1;
			msg_error("Fork error\n");
		}
		if (pid == 0)
			exec_route_child (data, node, env);
		else
			waitpid(pid, NULL, 0);
		/*if (check_f_d(node) == 0)
			g_status = 1;*/
	}
}