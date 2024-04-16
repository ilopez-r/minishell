/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:17:47 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/09 16:05:26 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(unsigned long long ptr, int fd)
{
	int	count;

	count = 0;
	count += ft_printstr("0x", fd);
	count += ft_printhexa(ptr, 'x', fd);
	return (count);
}
