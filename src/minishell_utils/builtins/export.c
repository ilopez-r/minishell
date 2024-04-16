/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:08:11 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 13:27:11 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

static t_env	*get_first(t_data *data)
{
	t_env	*first;
	t_env	*aux;

	aux = data->env;
	first = data->env;
	while (aux)
	{
		if (export_cmp(first->name, aux->name) < 0 && aux->index == 0)
			first = aux;
		aux = aux->next;
	}
	return (first);
}

void	set_index(t_data *data)
{
	int		index;
	t_env	*first;
	t_env	*aux;

	index = 1;
	first = data->env;
	aux = data->env;
	while (aux)
	{
		aux->index = 0;
		aux = aux->next;
	}
	while (index <= env_size(data->env))
	{
		aux = data->env;
		while (aux)
		{
			if (export_cmp(first->name, aux->name) > 0 && aux->index == 0)
				first = aux;
			aux = aux->next;
		}
		first->index = index;
		first = get_first(data);
		index++;
	}
}

static void	export_exe_content(t_data *data, char *s, char **tmp, t_env *aux)
{
	t_env	*new;

	tmp = ft_split(s, '=');
	if (!tmp)
		return ;
	if (check_node(data, tmp) == EXIT_SUCCESS)
	{
		free_dptr(tmp);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(tmp[0]);
	if (tmp[1] == NULL)
		new->content = ft_strdup("\"\"");
	else if (tmp[1])
		new->content = ft_strjoin("=", tmp[1]);
	new->index = 0;
	aux = data->env;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	new->next = NULL;
	free_dptr(tmp);
}

void	export_exe(t_data *d, char **s, int index, int fd)
{
	set_index(d);
	if (s[1])
		export_exe_content(d, s[1], NULL, d->x);
	else if (s[1] == NULL)
	{
		while (d->x)
		{
			if (d->x->index == index && index++)
			{
				d->ctnt = ft_split(d->x->content, '=');
				if (ft_strncmp(d->x->content, "\"\"\0", 3) == 0
					|| (d->ctnt[0] && d->ctnt[0][1] == '\"'))
					ft_printf(fd, "declare -x %s\n", d->x->name);
				else
					ft_printf(fd, "declare -x %s=\"%s\"\n", d->x->name,
						d->ctnt[0]);
				d->x = d->env;
				if (d->ctnt != NULL)
					free_dptr(d->ctnt);
			}
			else if (d->x->index != index)
				d->x = d->x->next;
		}
	}
	g_status = 0;
}
