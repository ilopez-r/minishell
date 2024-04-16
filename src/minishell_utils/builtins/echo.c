/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:17:02 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/15 15:41:29 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_print(char **s, int args, int fd)
{
	int	i;

	i = 0;
	while (s[args][i])
	{
		ft_printf(fd, "%c", s[args][i]);
		if (s[args][i] == '\0')
			break ;
		i++;
	}
}

void	echo_args_loop(char **s, int args, int fd)
{
	while (s[args])
	{
		echo_print(s, args, fd);
		if (s[args + 1] || s[args][0] == '\0')
			ft_printf(fd, " ");
		args++;
	}
}

void	echo_exe(char **s, int option, int fd)
{
	int	args;

	args = 0;
	while (s[args])
		args++;
	if (args > 1)
	{
		args = 0;
		if (s[1] && !ft_strncmp(s[1], "-n", 2))
		{
			option = 1;
			args = 2;
			echo_args_loop(s, args, fd);
		}
		else
		{
			args = 1;
			echo_args_loop(s, args, fd);
		}
	}
	if (option == 0)
		ft_printf(fd, "\n");
	g_status = 0;
}
