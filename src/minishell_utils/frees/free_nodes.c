/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:58 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/04 17:48:08 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_cmd(t_list **lst)
{
	free(((t_parser *)((*lst)->content))->full_cmd);
	((t_parser *)((*lst)->content))->full_cmd = NULL;
	free(((t_parser *)((*lst)->content))->route);
	((t_parser *)((*lst)->content))->route = NULL;
	if (((t_parser *)((*lst)->content))->in != 0)
		close(((t_parser *)((*lst)->content))->in);
	if (((t_parser *)((*lst)->content))->out != 1)
		close(((t_parser *)((*lst)->content))->out);
	free(((t_parser *)((*lst)->content)));
	(*lst)->content = NULL;
}

void	free_nodes(t_list **lst)
{
	t_list	*aux;
	int		i;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		i = -1;
		if (((t_parser *)((*lst)->content))->full_cmd)
		{
			while (((t_parser *)((*lst)->content))->full_cmd[++i])
			{
				free(((t_parser *)((*lst)->content))->full_cmd[i]);
				((t_parser *)((*lst)->content))->full_cmd[i] = NULL;
			}
		}
		free_cmd(lst);
		free((*lst));
		*lst = aux;
	}
	*lst = NULL;
}
