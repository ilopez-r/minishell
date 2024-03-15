/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:08:43 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/15 13:08:26 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*new;

	new = lst;
	if (lst == 0)
		return (0);
	while (new->next != 0)
		new = new->next;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*final;

	if (*lst != 0)
	{
		final = ft_lstlast_env(*lst);
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
			exit (EXIT_FAILURE);
		line = ft_split(env[i], '=');
		aux->name = ft_strdup(line[0]);
		if (line[1] == NULL)
			aux->content = ft_strdup("=");
		else
			aux->content = ft_strjoin("=", line[1]);
		aux->index = 0;
		aux->next = NULL;
		ft_lstadd_back_env(&data->env, aux);
		//free_dptr(line);
	}
	//poner el índice
}

void	env_exe(t_data *data)
{
	t_env	*aux;

	aux = data->env;
	while (aux != NULL)
	{
		printf("%s%s\n", aux->name, aux->content);
		aux = aux->next;
	}
}
