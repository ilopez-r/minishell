/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:29:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/14 16:09:56 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}atexit(ft_leaks); */

static void	init_struct(t_data *data)
{
	data->line = NULL;
	data->path = NULL;
}

int	input(t_data *data, char **env)
{
	
}

int	minishell(t_data *data, char **env)
{
	piti_shell();
	cigarrette();
	get_env (data, env);
	while (69)
	{
		//hacer minitalk;
		if (prompt(data) == 1)
			exit(EXIT_FAILURE);
		if (ft_strncmp(data->line, "\0", 1) >= 1)
			add_history(data->line);
		if (input(data, env) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		exit (EXIT_FAILURE);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit (EXIT_FAILURE);
	init_struct(data);
	if (minishell(data, env) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
