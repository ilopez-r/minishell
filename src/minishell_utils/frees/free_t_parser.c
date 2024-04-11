/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:43:32 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/11 18:52:53 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_t_parser(t_parser *n)
{
	if (n == NULL)
		return ;
	if (n->full_cmd != NULL)
	{
		free_dptr(n->full_cmd);
		n->full_cmd = NULL;
	}
	if (n->route != NULL)
		free(n->route);
	if (n->in != 0)
		close(n->in);
	if (n->out != 1)
		close(n->out);
	free(n);
}
