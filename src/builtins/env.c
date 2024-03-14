/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:08:43 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/14 16:10:32 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*final;

	if (*lst != 0)
	{
		final = ft_lstlast(*lst);
		final->next = new;
	}
	else
		*lst = new;
}

void	get_env(t_data *data, char **env)
{
	int		i;
	char	**line;
	t_env	*aux;

	i = -1;
	while (env[++i] != NULL)
	{
		aux = ft_calloc(1, sizeof(t_env));
		if (!aux)
			return (EXIT_FAILURE);
		line = ft_split(env[i], '=');
		aux->name = ft_strdup(line[0]);
		if (line[1] == NULL)
			aux->content = ft_strdup("=");
		else
			aux->content = ft_strjoin("=", line[1]);
		aux->index = 0;
		aux->next = NULL;
		ft_listadd_back_env(&data->env, aux);
		free_dptr(line);
	}
	//poner el índice
}
