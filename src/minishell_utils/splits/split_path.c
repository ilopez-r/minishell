/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:23:50 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/11 18:09:47 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	split_path(t_data *data)
{
	t_env	*aux;

	aux = data->env;
	if (data->path != NULL)
	{
		free_dptr(data->path);
		data->path = NULL;
	}
	while (aux)
	{
		if (ft_strncmp(aux->name, "PATH", 4) == 0)
		{
			data->path = ft_split (aux->content + 1, ':');
			break ;
		}
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}
