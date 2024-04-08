/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:43:32 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/05 20:17:21 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_t_parser(t_parser *n)
{
	//int			i;

	if (n == NULL)
		return ;
	//i = -1;
	if (n->full_cmd != NULL)
		free_dptr(n->full_cmd);
	if (n->route != NULL)
		free(n->route);
	if (n->in != 0)
		close(n->in);
	if (n->out != 1)
		close(n->out);
	free(n);
}
