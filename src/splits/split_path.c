/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:23:50 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 22:35:56 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_path(t_data *data)
{
	t_env	*aux;

	aux = data->env;
	//if (data->path != NULL)
		//free_dptr(data->path);
	while (aux)
	{
		if (ft_strncmp(aux->name, "PATH", 4) == 0)
		{
			data->path = ft_split (aux->content, ':');
			break ;
		}
		aux = aux->next;
	}
	if (data->path == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
