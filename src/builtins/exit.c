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

#include "../minishell.h"

int	exit_exe(t_data *data, t_parser *nodes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (nodes->full_cmds[i])
		i++;
	if (i > 2)
		return (printf("exit\nPITISHELL: exit: too many arguments\n"),
			EXIT_FAILURE);
	if (i >= 2)
	{
		while (nodes->full_cmds[1][j])
		{
			if (ft_isdigit(nodes->full_cmds[1][j]) == 0)
			{
				printf("exit\nPITISHELL: exit: %s: numeric argument required\n",
					nodes->full_cmds[1]);
				break ;
			}
			j++;
		}
	}
	free_path(data);
	//exit (g_status);
}
