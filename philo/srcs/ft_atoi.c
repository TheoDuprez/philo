/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:27:59 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/05 15:47:25 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check(int sign);

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res != (res * 10) / 10)
			return (ft_check(sign));
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

static int	ft_check(int sign)
{
	if (sign == 1)
	{
		sign = -1;
		return (sign);
	}
	else
	{
		sign = 0;
		return (sign);
	}
}
