/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:52:22 by ismael            #+#    #+#             */
/*   Updated: 2024/04/11 12:01:49 by ilopez-r         ###   ########.fr       */
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
		export_exe(d, n->full_cmd, 1, n->out);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "exit\0", 5) == 0)
	{
		if (exit_exe(d, n) == EXIT_FAILURE)
			return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_builtins(t_parser *n)
{
	if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "cd\0", 3) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "echo\0", 5) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "env\0", 4) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "pwd\0", 4) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "unset\0", 6) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "export\0", 7) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "exit\0", 5) == 0)
		return (n->route = ft_strdup("builtin"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_route(t_data *data, t_parser *n)
{
	char	*routetmp;
	char	*routetmp2;
	int		i;

	i = -1;
	while (data->path[++i] != NULL)
	{
		if (check_builtins (n) == 1)
			return (EXIT_SUCCESS);
		routetmp = ft_strjoin(data->path[i], "/");
		routetmp2 = ft_strjoin(routetmp, n->full_cmd[0]);
		free(routetmp);
		if (access(routetmp2, F_OK) == 0 && access(routetmp2, X_OK) == 0)
		{
			n->route = ft_strdup(routetmp2);
			free(routetmp2);
			routetmp2 = NULL;
			return (EXIT_SUCCESS);
		}
		free(routetmp2);
	}
	if (access(n->full_cmd[0], F_OK) == 0 && access(n->full_cmd[0], X_OK) == 0)
		n->route = ft_strdup(n->full_cmd[0]);
	if (n->route == NULL)
	{
		//g_status = 127;
		return (printf("error: %s: command not found\n",
				n->full_cmd[0]), 127);
	}
	return (EXIT_SUCCESS);
}

int	ft_catcatls(t_data *data, char **env)
{
	t_list	*aux;
	char	*line;
	int		j;

	aux = data->nodes;
	if (aux->next != NULL && aux->next->next != NULL
		&& ft_strncmp(((t_parser *)(aux->next->content))->full_cmd[0], "cat\0", 4) == 0
		&& ((t_parser *)(aux->next->content))->in == 0
		&& ((t_parser *)(aux->next->content))->out == 1
		&& ft_strncmp(((t_parser *)(aux->next->next->content))->full_cmd[0], "cat\0", 4) != 0)
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

int	executer(t_data *data, char **env, t_parser *node)
{
	int		i;
	t_list	*aux;
	t_list	*aux2;

	i = 0;
	aux = data->nodes;
	aux2 = data->nodes;
	//minitalk;
	while (data->cmds[i] != NULL && ((t_parser *)(aux->content))->full_cmd)
	{
		if (get_route(data, ((t_parser *)(aux->content))) == 127)
			//g_status = 127
			return (EXIT_SUCCESS);
		i++;
		if (aux->next != NULL)
			aux = aux->next;
	}
	if (((t_parser *)(aux->content))->full_cmd == NULL)
		((t_parser *)(aux->content))->route = NULL;
	//ft_print_cmds (data);
	//ft_print_nodes (data);
	if (node && node->full_cmd && node->full_cmd[0])
	{
		if ((!ft_strncmp(((t_parser *)(aux2->content))->full_cmd[0], "cat\0", 4)
			&& ((t_parser *)(aux2->content))->in == 0
			&& ((t_parser *)(aux2->content))->out == 1)
			&& ft_catcatls (data, env) == 0)
			return (EXIT_SUCCESS);
		if (i > 1)
		{
			while (aux2)
			{
				if (aux2->next == NULL
					&& ft_strncmp(((t_parser *)(aux2->content))->route, "builtin\0", 8) == 0)
					builtins_executer(((t_parser *)(aux2->content)), data);
				else
					exec_route_pipes(data, ((t_parser *)(aux2->content)), env, aux2);
				aux2 = aux2->next;
			}
		}
		else if (i == 1)
			exec_route (data, node, env);
	}
	//else if ()
	return (EXIT_SUCCESS);
}
