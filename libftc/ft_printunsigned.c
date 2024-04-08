/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:24:41 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/01/15 11:20:18 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunsigned(unsigned long long int n)
{
	int		count;
	char	c;

	count = 0;
	if (n > 9)
		count += ft_printdec(n / 10);
	c = n % 10 + '0';
	count += ft_printchar(c);
	return (count);
}
