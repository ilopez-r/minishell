/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:49:42 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/13 17:50:40 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piti_shell(void)
{
	printf(" _____  _____ _______ _____  _____ _    _ ______ _      _\n");
	printf("|  __ \\|_   _|__   __|_   _|/ ____| |  | |  ____| |    | |\n");
	printf("| |__| | | |    | |    | | | (___ | |__| | |__  | |    | |\n");
	printf("|  ___/  | |    | |    | |  \\___ \\|  __  |  __| | |    | |\n");
	printf("| |     _| |_   | |   _| |_ ____) | |  | | |____| |____| |____\n");
	printf("|_|    |_____|  |_|  |_____|_____/|_|  |_|______|______|______|\n");
	printf("\n");
}

void	cigarrette(void)
{
	printf("	a,  8a\n");
	printf("  	`8, `8)                            ,adPPRg,\n");
	printf(" 	 8)  ]8                        ,ad88888888b\n");
	printf("	 ,8' ,8'                    ,gPPR88888888888\n");
	printf("	,8' ,8'                 ,ad8``   `Y88888888P\n");
	printf("	8)  8)              ,ad8``        (888888``\n");
	printf("	8,  8,          ,ad8``            d888`\n");
	printf("	`8, `8,     ,ad8``            ,ad8``\n");
	printf("	 `8, `` .ad8              .ad8``\n");
	printf("	    ,gPPR8b           ,ad8``\n");
	printf("	   dP:::::Yb      ,ad8``\n");
	printf(" 	  8):::::(8  ,ad8``\n");
	printf(" 	  Yb:;;;:d888``   ilopez-r\n");
	printf("	   `8ggg8P`       alirola-\n");
	printf("\n");
}

int	prompt(t_data *data)
{
	char	cur_dir[500];
	char	*dir;

	dir = ft_strjoin(getcwd(cur_dir, sizeof(cur_dir)), " % ");
	data->line = readline(dir);
	if (data->line == NULL)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
