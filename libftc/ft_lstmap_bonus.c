/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:44:52 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/05/23 13:52:14 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*final;
	void	*content;

	final = 0;
	if (lst == 0)
		return (0);
	while (lst != 0)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (new == 0)
		{
			ft_lstclear(&final, del);
			del(content);
			return (0);
		}
		ft_lstadd_back(&final, new);
		lst = lst->next;
	}
	return (final);
}
