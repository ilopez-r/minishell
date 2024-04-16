/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:06:35 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/04 15:06:35 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	continue_unset(t_env *del)
{
	free(del->name);
	if (del->content != NULL)
		free(del->content);
	free(del);
	del = NULL;
	g_status = 0;
}

void	unset_exe(t_data *data, char *name)
{
	t_env	*del;
	t_env	*prev;
	t_env	*aux;

	if (!name)
		return ;
	aux = data->env;
	prev = NULL;
	while (aux)
	{
		if (!ft_strncmp(aux->name, name, ft_strlen(name)))
		{
			del = aux;
			if (prev)
				prev->next = aux->next;
			else
				data->env = aux->next;
			continue_unset(del);
			return ;
		}
		prev = aux;
		aux = aux->next;
	}
	check_path(data);
	g_status = 1;
}
