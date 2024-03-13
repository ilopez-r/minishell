/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:23:50 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/13 16:23:59 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_path(char **path, t_data *data)
{
	while (ft_strncmp(*path, "PATH", 4) != 0)
		path++;
	*path = *path + 5;
	data->path = ft_split (*path, ':');
	if (data->path == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}