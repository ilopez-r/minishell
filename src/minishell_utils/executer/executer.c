/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:52:22 by ismael            #+#    #+#             */
/*   Updated: 2024/04/16 13:27:59 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins_executer(t_parser *n, t_data *d)
{
	if (!(n->full_cmd))
		return (EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "cd\0", 3) == 0)
		cd_exe(d, n->full_cmd, 0);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "echo\0", 4) == 0)
		echo_exe (n->full_cmd, 0, n->out);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "env\0", 4) == 0)
		env_exe(d, n->out);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "pwd\0", 4) == 0)
		pwd_exe(n->out);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "unset\0", 6) == 0)
		unset_exe(d, n->full_cmd[1]);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "export\0", 7) == 0)
	{
		d->x = d->env;
		export_exe(d, n->full_cmd, 1, n->out);
	}
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "exit\0", 5) == 0)
	{
		if (exit_exe(d, n, n->out, 0) == EXIT_FAILURE)
			return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_catcatls(t_data *data, char **env)
{
	t_list	*aux;
	char	*line;
	int		j;

	aux = data->nodes;
	if (aux->next != NULL && aux->next->next != NULL
		&& ft_strncmp(((t_parser *)(aux->next->content))->full_cmd[0],
		"cat\0", 4) == 0
		&& ((t_parser *)(aux->next->content))->full_cmd[1] == NULL
		&& ((t_parser *)(aux->next->content))->in == 0
		&& ((t_parser *)(aux->next->content))->out == 1
		&& ft_strncmp(((t_parser *)(aux->next->next->content))->full_cmd[0],
		"ls\0", 3) == 0)
	{
		exec_route (data, ((t_parser *)(aux->next->next->content)), env);
		line = get_next_line(0);
		j = 0;
		while (line && ++j < 2)
		{
			free (line);
			line = get_next_line(0);
		}
		return (free (line), EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	executer(t_data *data, char **env, t_parser *n, t_list *a)
{
	signal(SIGINT, cat_ctrlc);
	signal(SIGQUIT, cat_ctrlbackslash);
	if (n && n->full_cmd && n->full_cmd[0])
	{
		if (data->f_pipe == 1)
		{
			if ((!ft_strncmp(n->full_cmd[0], "cat\0", 4)
					&& n->full_cmd[1] == NULL && n->in == 0 && n->out == 1)
				&& ft_catcatls (data, env) == 0)
				return (EXIT_SUCCESS);
			while (a)
			{
				if (a->next == NULL
					&& !ft_strncmp(((t_parser *)(a->content))->route, "b\0", 2))
					builtins_executer(((t_parser *)(a->content)), data);
				else
					exec_route_pipes(data, ((t_parser *)(a->content)), env, a);
				a = a->next;
			}
		}
		else if (data->f_pipe == 0)
			exec_route (data, n, env);
	}
	return (EXIT_SUCCESS);
}
