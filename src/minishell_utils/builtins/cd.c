/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:14:32 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/15 12:38:02 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_pwd(t_data *data)
{
	char	dir[500];
	t_env	*aux;

	aux = data->env;
	while (aux)
	{
		if (ft_strncmp(aux->name, "PWD", 3) == EXIT_SUCCESS)
		{
			free(aux->content);
			aux->content = ft_strdup(getcwd(dir, 500));
			if (!aux->content)
				return ;
			break ;
		}
		aux = aux->next;
	}
	g_status = 0;
}

void	get_home_path(t_data *data, char *s)
{
	t_env	*aux;
	char	**ctnt;

	aux = data->env;
	while (aux)
	{
		if (ft_strncmp(aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
		{
			ctnt = ft_split(aux->content, '=');
			data->tmp = ctnt[0];
			break ;
		}
		aux = aux->next;
	}
}

void	change_oldpwd(t_data *data, char *dir)
{
	t_env	*aux;

	aux = data->env;
	while (aux)
	{
		if (ft_strncmp(aux->name, "OLDPWD", 6) == EXIT_SUCCESS)
		{
			free(aux->content);
			if (!dir)
				aux->content = ft_strdup(getcwd(dir, 500));
			else
				aux->content = ft_strdup(dir);
			if (!aux->content)
				return ;
			break ;
		}
		aux = aux->next;
	}
}

void	change_cd(t_data *data)
{
	change_oldpwd(data, NULL);
	get_home_path(data, "HOME\0");
	chdir(data->tmp);
	change_pwd(data);
	g_status = 0;
}

void	cd_exe(t_data *d, char **s, int flag)
{
	char	dir[500];

	if (ft_strncmp(s[0], "cd\0", 3) == EXIT_SUCCESS && !s[1])
		change_cd(d);
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		getcwd(dir, 500);
		flag = chdir(s[1]);
		if (flag == 0)
		{
			change_oldpwd(d, dir);
			change_pwd(d);
		}
		else if (flag == -1)
		{
			d->tmp = ft_strjoin("error: cd: ", s[1]);
			if (!d->tmp)
				return ;
			d->cd_error = ft_strjoin(d->tmp, ": No such file or directory");
			if (!d->cd_error)
				return ;
			ft_putendl_fd(d->cd_error, 2);
			free_cd_error(d);
		}
	}
}
