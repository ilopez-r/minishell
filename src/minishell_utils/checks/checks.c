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

int	check_builtins(t_parser *n)
{
	if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "cd\0", 3) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "echo\0", 5) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "env\0", 4) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "pwd\0", 4) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "unset\0", 6) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "export\0", 7) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	else if (n->full_cmd[0] && ft_strncmp(n->full_cmd[0], "exit\0", 5) == 0)
		return (n->route = ft_strdup("b"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		{
			data->path_flag = 0;
			if (data->path != NULL)
			{
				free_dptr(data->path);
				data->path = NULL;
			}
		}
		aux = aux->next;
	}
}

int	check_quotes(char *s)
{
	int		i;
	int		fq_simple;
	int		fq_double;

	i = 0;
	fq_simple = 0;
	fq_double = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		else if (s[i] == '\"' && !fq_simple)
			fq_double = !fq_double;
		i++;
	}
	if (fq_double || fq_simple)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
