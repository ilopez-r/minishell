/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:51:41 by alirola-          #+#    #+#             */
/*   Updated: 2024/03/19 16:51:41 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_exe(t_data *data, t_parser *n, int fd, int i)
{
	ft_printf (fd, "exit\n");
	if (n->full_cmd[1] != NULL && n->full_cmd[2] != NULL)
		return (ft_printf(fd, "error: exit: too many arguments\n"), 1);
	else if (n->full_cmd[1] != NULL)
	{
		i = -1;
		if (n->full_cmd[1][0] == '+' || n->full_cmd[1][0] == '-')
			i++;
		while (n->full_cmd[1][++i])
		{
			if (ft_isdigit(n->full_cmd[1][i]) == 0)
			{
				ft_printf(fd, "error: exit: %s: not an int\n", n->full_cmd[1]);
				break ;
			}
		}
	}
	if (data->path != NULL)
	{
		free_dptr(data->path);
		data->path = NULL;
	}
	exit (g_status);
}
