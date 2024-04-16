/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:49:23 by ismael            #+#    #+#             */
/*   Updated: 2024/04/15 16:30:57 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_route_pipes_final_2(t_parser *node, char **env)
{
	if (node->out != STDOUT_FILENO)
	{
		if (dup2(node->out, STDOUT_FILENO) == -1)
			msg_error("Last command wrt error\n");
		close (node->out);
	}
	g_status = execve(node->route, node->full_cmd, env);
}

void	exec_route_pipes_final(t_data *d, t_parser *node, char **env)
{
	if (node->in != 0 && d->f_hd == 1)
	{
		if (dup2(node->in, STDIN_FILENO) == -1)
			msg_error_pipes("Here_doc read error\n");
	}
	else if (node->in != 0 && d->f_hd == 0)
	{
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
	exec_route_pipes_final_2 (node, env);
}

void	exec_route_pipes_child2(t_data *d, t_parser *n, char **env, t_list *aux)
{
	if (n->out == 1)
	{
		if (dup2(d->fd[1], STDOUT_FILENO) == -1)
			msg_error_pipes("Write error\n");
	}
	else if (n->out != 1)
	{
		if (dup2(n->out, STDOUT_FILENO) == -1)
			msg_error_pipes("Outfile wrt error\n");
		close (n->out);
	}
	close (d->fd[1]);
	if (ft_strncmp(n->route, "b\0", 2) == 0)
	{
		if (n->out == 1 && ((t_parser *)(aux->next->content))->in == 0)
			((t_parser *)(aux->next->content))->out = d->fd[0];
		builtins_executer(n, d);
		exit (1);
	}
	else
		g_status = execve(n->route, n->full_cmd, env);
}

void	exec_route_pipes_child(t_data *d, t_parser *n, char **env, t_list *aux)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (d->f_hd == 1)
	{
		if (dup2(n->in, STDIN_FILENO) == -1)
			msg_error_pipes("Here_doc read error\n");
		unlink("here_doc.tmp");
		close (n->in);
	}
	else if (n->in != STDIN_FILENO)
	{
		if (dup2(n->in, STDIN_FILENO) == -1)
			msg_error_pipes("Infile read error\n");
		close (n->in);
	}
	close (d->fd[0]);
	exec_route_pipes_child2(d, n, env, aux);
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
	check_f_d(node);
}
