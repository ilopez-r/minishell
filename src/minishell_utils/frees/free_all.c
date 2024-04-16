/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:12:37 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/11 17:38:56 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_full(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	lst->index = 0;
	free(lst->content);
	free(lst);
	lst = NULL;
}

void	free_env(t_env **lst)
{
	t_env	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		free_env_full(*lst);
		*lst = aux;
	}
	*lst = NULL;
}

void	free_all(t_data *data)
{
	if (data->path != NULL)
	{
		free_dptr(data->path);
		data->path = NULL;
	}
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->env != NULL)
		free_env(&data->env);
	if (data->nodes != NULL)
	{
		free_nodes(&data->nodes);
		data->nodes = NULL;
	}
	if (data->cmds != NULL)
	{
		free_dptr (data->cmds);
		data->cmds = NULL;
	}
	free(data);
}
