/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:23:44 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/16 18:23:36 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cat_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		printf("\033[K\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}

void	cat_ctrlbackslash(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
