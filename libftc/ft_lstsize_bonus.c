/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:51:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/05/22 16:21:27 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*new;
	int		i;

	i = 1;
	new = lst;
	if (lst == 0)
		return (0);
	while (new->next != 0)
	{
		i++;
		new = new->next;
	}
	return (i);
}
