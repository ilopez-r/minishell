/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:49:23 by ismael            #+#    #+#             */
/*   Updated: 2024/04/11 16:14:52 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	msg_error_pipes(char *str)
{
	unlink("here_doc.tmp");
	//g_status = 1;
	perror(str);
	exit(EXIT_FAILURE);
}

void	exec_route_pipes_final(t_data *d, t_parser *node, char **env)
{
	if (node->in != 0)
	{
		if (d->f_hd == 1)
		{
			if (dup2(node->in, STDIN_FILENO) == -1)
				msg_error_pipes("Here_doc read error\n");
		}
		else
			if (dup2(node->in, STDIN_FILENO) == -1)
				msg_error_pipes("Infile read error\n");
	}
	else if (d->fd[1] == STDOUT_FILENO)
	{
		if (dup2(d->fd[0], STDIN_FILENO) == -1)
			msg_error("Read error\n");
	}
	else if (node->in == 0)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error_pipes("Infile read error\n");
	}
	close (node->in);
	if (node->out != STDOUT_FILENO)
	{
		if (dup2(node->out, STDOUT_FILENO) == -1)
			msg_error("Last command wrt error\n");
		close (node->out);
	}
	//g_status = execve(node->route, node->full_cmd, env);
	//sustituir lo de abajo por g_status
	if (execve(node->route, node->full_cmd, env) == -1)
		msg_error("Last command exec error\n");
}

void	exec_route_pipes_child(t_data *d, t_parser *node, char **env, t_list *aux)
{
	//minitalk;
	if (d->f_hd == 1)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error_pipes("Here_doc read error\n");
		unlink("here_doc.tmp");
		close (node->in);
	}
	else if (node->in != STDIN_FILENO)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error_pipes("Infile read error\n");
		close (node->in);
	}
	close (d->fd[0]);
	if (node->out == 1)
	{
		if (dup2(d->fd[1], STDOUT_FILENO) == -1)
			msg_error_pipes("Write error\n");
	}
	else if (node->out != 1)
	{
		if (dup2(node->out, STDOUT_FILENO) == -1)
			msg_error_pipes("Outfile wrt error\n");
		close (node->out);
	}
	close (d->fd[1]);
	//g_status = execve(node->route, node->full_cmd, env);
	//sustituir lo de abajo por g_status
	if (ft_strncmp(node->route, "b\0", 2) == 0)
	{
		if (node->out == 1 && ((t_parser *)(aux->next->content))->in == 0)
			((t_parser *)(aux->next->content))->out = d->fd[0];
		builtins_executer(node, d);
		exit (1);
	}
	else if (execve(node->route, node->full_cmd, env) == -1)
		msg_error_pipes("Exec error\n");
}

void	exec_route_pipes(t_data *data, t_parser *node, char **env, t_list *aux)
{
	pid_t		pid;

	if (pipe(data->fd) == -1)
		msg_error("Pipe error\n");
	pid = fork();
	if (pid == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		msg_error("Fork error\n");
	}
	if (pid == 0)
	{
		if (aux->next != NULL)
			exec_route_pipes_child (data, node, env, aux);
		else
			exec_route_pipes_final (data, node, env);
	}
	if (aux->next && ((t_parser *)(aux->next->content))->in == 0)
		((t_parser *)(aux->next->content))->in = data->fd[0];
	else
		close(data->fd[0]);
	close (data->fd[1]);
	waitpid(pid, NULL, 0);
}
