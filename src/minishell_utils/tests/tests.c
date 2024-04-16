/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:58:04 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 13:30:37 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_cmds(t_data *d)
{
	int	i;

	i = 0;
	while (d->cmds[i] != NULL)
	{
		printf("cmds %i: %s\n", i, d->cmds[i]);
		i++;
	}
	printf("\n");
}
//ft_print_cmds (d); después del split_cmds

void	ft_print_nodes(t_data *d)
{
	t_list	*aux;
	int		i;

	aux = d->nodes;
	while (aux)
	{
		i = 0;
		printf("route: %s\n", ((t_parser *)(aux->content))->route);
		if (((t_parser *)(aux->content))->full_cmd)
		{
			while (((t_parser *)(aux->content))->full_cmd[i])
			{
				printf("full_cmd %i: %s\n", i,
					((t_parser *)(aux->content))->full_cmd[i]);
				i++;
			}
		}
		printf("Outfile: %d\nInfile: %d\n\n",
			((t_parser *)(aux->content))->out,
			((t_parser *)(aux->content))->in);
		aux = aux->next;
	}
}
//ft_print_nodes (d); después del get route

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
//atexit(ft_leaks);