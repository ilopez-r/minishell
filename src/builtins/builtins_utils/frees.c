/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:37:47 by alirola-          #+#    #+#             */
/*   Updated: 2024/03/21 13:37:47 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	if (data->path)
	{
		while (data->path[i])
		{
			free(data->path[i]);
			data->path[i++] = NULL;
		}
		free(data->path);
		data->path = NULL;
	}
}

void	free_dptr(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free (tmp);
}

void	free_cd_error(t_data *data)
{
	free(data->tmp);
	free(data->cd_error);
	//g_status = 1;
}
