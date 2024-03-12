/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:47:22 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/04/27 18:03:08 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	signo;
	int	num;

	a = 0;
	signo = 1;
	num = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			signo = -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		num = num * 10 + (str[a] - 48);
		a++;
	}
	return (num * signo);
}

/*
int	main(void)
{
	char	*str;
	int		a;

	str = "  ---+--+ 1234ab456";
	a = ft_atoi(str);
	printf("%d\n", a);
	return (0);
}
*/