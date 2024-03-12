/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:24:36 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/01/15 11:13:55 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa(unsigned long long n, char c)
{
	unsigned long long	count;

	count = 0;
	if (n >= 16)
		count += ft_printhexa(n / 16, c);
	if (c == 'x')
		ft_printchar("0123456789abcdef" [n % 16]);
	if (c == 'X')
		ft_printchar("0123456789ABCDEF" [n % 16]);
	count++;
	return (count);
}
