/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:14:32 by alirola-          #+#    #+#             */
/*   Updated: 2024/03/14 17:58:48 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_cd(t_data *data)
{
	char	dir[500];
	t_env	*aux;
	
	aux = data->line;
	while (aux)
	{
		if (ft_strncmp(aux->name, "OLDPWD", 6) == 0)
		{
			
		}
	}
}

void	cd_exe(t_data *data, char **s, int flag)
{
	char	dir[500];

	if (ft_strncmp(s[0], "cd\0", 3) && s[1] == NULL)
		change_cd(data);
	
}