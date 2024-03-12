/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:24:50 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/01/15 11:12:10 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_filter(char const *str, int i, va_list *args)
{
	int	filtrated_c;

	filtrated_c = 0;
	if (str[i] == 'c')
		filtrated_c += ft_printchar(va_arg(*args, int));
	if (str[i] == 's')
		filtrated_c += ft_printstr(va_arg(*args, char *));
	if (str[i] == 'x' || str[i] == 'X')
		filtrated_c += ft_printhexa(va_arg(*args, unsigned int), str[i]);
	if (str[i] == 'p')
		filtrated_c += ft_printptr(va_arg(*args, unsigned long long));
	if (str[i] == 'd')
		filtrated_c += ft_printdec(va_arg(*args, int));
	if (str[i] == 'i')
		filtrated_c += ft_printdec(va_arg(*args, int));
	if (str[i] == '%')
		filtrated_c += ft_printchar('%');
	if (str[i] == 'u')
		filtrated_c += ft_printunsigned(va_arg(*args, unsigned int));
	return (filtrated_c);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start (args, str);
	while (str[i] != 0)
	{
		if (str[i] != '%')
		{
			ft_printchar(str[i]);
			c++;
		}
		else
		{
			i++;
			c += ft_filter(str, i, &args);
		}
		i++;
	}
	va_end (args);
	return (c);
}
