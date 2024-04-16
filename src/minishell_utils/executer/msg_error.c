/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:30:15 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/15 15:39:57 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	msg_error_pipes(char *str)
{
	unlink("here_doc.tmp");
	g_status = 1;
	perror(str);
	exit(EXIT_FAILURE);
}

void	msg_error(char *str)
{
	unlink("here_doc.tmp");
	g_status = 1;
	perror(str);
	exit(EXIT_FAILURE);
}
