/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:06:18 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/11 12:06:39 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc(t_data *data, t_parser **n, char *line)
{
	(*n)->in = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*n)->in == -1)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(data->dup_stdin);
		if (!line)
			msg_error("Get_next_line error");
		if (!ft_strncmp(data->in, line, ft_strlen(data->in)))
		{
			free(line);
			close (data->dup_stdin);
			break ;
		}
		ft_putstr_fd(line, (*n)->in);
		free(line);
	}
	close((*n)->in);
	(*n)->in = open("here_doc.tmp", O_RDONLY);
	data->dup_stdin = dup(STDIN_FILENO);
	if ((*n)->in == -1)
		msg_error("Here_doc open file1 error");
}
