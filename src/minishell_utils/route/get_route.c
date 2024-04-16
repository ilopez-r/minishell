/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_route.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:17:50 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 11:36:47 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_dir(char *aux)
{
	DIR	*dir;

	dir = opendir(aux);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

int	get_route(t_data *data, t_parser *n, int i)
{
	char	*routetmp;
	char	*routetmp2;

	if (n->full_cmd[0] == NULL)
		return (printf("error: command not found\n"), 1);
	if (check_builtins (n) == 1)
		return (EXIT_SUCCESS);
	while (data->path != NULL && data->path[++i] != NULL)
	{
		routetmp = ft_strjoin(data->path[i], "/");
		routetmp2 = ft_strjoin(routetmp, n->full_cmd[0]);
		free(routetmp);
		if (access(routetmp2, F_OK) == 0 && access(routetmp2, X_OK) == 0)
		{
			n->route = ft_strdup(routetmp2);
			return (free(routetmp2), routetmp2 = NULL, EXIT_SUCCESS);
		}
		free(routetmp2);
	}
	if (ft_dir(n->full_cmd[0]) == 0 && access(n->full_cmd[0], F_OK) == 0
		&& access(n->full_cmd[0], X_OK) == 0)
		n->route = ft_strdup(n->full_cmd[0]);
	if (n->route == NULL)
		return (printf("error: %s: command not found\n", n->full_cmd[0]), 1);
	return (EXIT_SUCCESS);
}

int	route(t_data *data, int i)
{
	t_list	*aux;

	aux = data->nodes;
	data->f_pipe = 0;
	while (data->cmds[i] != NULL && ((t_parser *)(aux->content))->full_cmd)
	{
		if (get_route(data, ((t_parser *)(aux->content)), -1) == 1)
			return (g_status = 127, EXIT_FAILURE);
		if (i == 1)
			data->f_pipe = 1;
		i++;
		if (aux->next != NULL)
			aux = aux->next;
	}
	if (((t_parser *)(aux->content))->full_cmd == NULL)
		((t_parser *)(aux->content))->route = NULL;
	return (EXIT_SUCCESS);
}
