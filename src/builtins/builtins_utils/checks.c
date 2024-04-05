/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:39:25 by alirola-          #+#    #+#             */
/*   Updated: 2024/03/19 16:39:25 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_path(t_data *data)
{
	t_env	*aux;

	aux = data->env;
	while (aux)
	{
		if (!ft_strncmp (aux->name, "PATH", 4))
		{
			data->path_flag = 1;
			return ;
		}
		else
			data->path_flag = 0;
		aux = aux->next;
	}
}

int	check_node(t_data *data, char **s)
{
	t_env	*aux;

	aux = data->env;
	while (aux)
	{
		if (ft_strncmp(aux->name, s[0], ft_strlen(s[0])) == EXIT_SUCCESS)
		{
			if (aux->content)
			{
				free(aux->content);
				if (s[1] == NULL)
					aux->content = ft_strjoin("=", "\"\"");
				else
					aux->content = ft_strjoin("=", s[1]);
			}
			else
				aux->content = ft_strdup(s[1]);
			return (EXIT_SUCCESS);
		}
		else
			aux = aux->next;
	}
	return (EXIT_FAILURE);
}
