/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:24:47 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/09 16:06:18 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printdec(long long int n, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0)
	{
		count += ft_printchar('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_printdec(n / 10, fd);
	}
	c = n % 10 + '0';
	count += ft_printchar(c, fd);
	return (count);
}
