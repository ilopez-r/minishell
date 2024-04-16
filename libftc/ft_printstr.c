/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:18:01 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/09 16:03:34 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == 0)
		str = "(null)";
	while (str[i] != '\0')
	{
		ft_printchar(str[i], fd);
		i++;
	}
	return (i);
}
