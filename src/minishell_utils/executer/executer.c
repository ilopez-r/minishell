/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:52:22 by ismael            #+#    #+#             */
/*   Updated: 2024/04/08 17:06:33 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins_executer(t_parser *node, t_data *d)
{
	if (!(node->full_cmd))
		return (EXIT_FAILURE);
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "pwd\0", 4) == 0)
		pwd_exe();
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "env\0", 4) == 0)
		env_exe(d);
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "unset\0", 6) == 0)
		unset_exe(d, node->full_cmd[1]);
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "cd\0", 3) == 0)
		cd_exe(d, node->full_cmd, 0);
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "export\0", 7) == 0)
		export_exe(d, node->full_cmd, 1);
	if (node->full_cmd[0] && ft_strncmp(node->full_cmd[0], "exit\0", 5) == 0)
	{
		if (exit_exe(d, node) == EXIT_FAILURE)
			return (EXIT_SUCCESS);
	}
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
	if (access(n->full_cmd[0], F_OK) == 0
		&& access(n->full_cmd[0], X_OK) == 0)
		n->route = ft_strdup(n->full_cmd[0]);
	if (n->route == NULL)
	{
		//g_status = 127;
		return (printf("error: %s: command not found\n",
				((t_parser *)data->nodes->content)->full_cmd[0]), 127);
	}
	return (EXIT_SUCCESS);
}

int	executer(t_data *data, char **env, t_parser *node)
{
	int		i;
	t_list	*aux;

	i = 0;
	aux = data->nodes;
	//minitalk;
	if (builtins_executer(node, data) == 1)
		return (EXIT_SUCCESS);
	else if (node && node->full_cmd && node->full_cmd[0]
		&& builtins_executer(node, data) == 0)
	{
		ft_print_cmds (data);
		while (data->cmds[i] != NULL)
		{
			if (get_route(data, ((t_parser *)(aux->content))) == 127)
				//g_status = 127
				return (EXIT_SUCCESS);
			i++;
			aux = aux->next;
		}
		ft_print_nodes (data);
		if (i > 1)
			exec_route_pipes (data, node, env);
		else if (i == 1)
			exec_route (data, node, env);
	}
	//else if ()
	return (EXIT_SUCCESS);
}
