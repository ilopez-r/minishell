/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:17:02 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/05 14:17:16 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_print(char **s, int args)
{
	int	i;

	i = 0;
	while (s[args][i])
	{
		printf("%c", s[args][i]);
		if (s[args][i] == '\0')
			break ;
		i++;
	}
}

void	echo_args_loop(char **s, int args)
{
	while (s[args])
	{
		echo_print(s, args);
		if (s[args + 1] || s[args][0] == '\0')
			printf(" ");
		args++;
	}
}

void	echo_exe(char **s, int option)
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
			echo_args_loop(s, args);
		}
		else
		{
			args = 1;
			echo_args_loop(s, args);
		}
	}
	if (option == 0)
		printf("\n");
}
