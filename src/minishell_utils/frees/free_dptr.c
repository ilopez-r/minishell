/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:36:11 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/03 14:36:11 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_dptr(char **tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		free (tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	if (tmp != NULL)
	{
		free (tmp);
		tmp = NULL;
	}
	tmp = NULL;
}
