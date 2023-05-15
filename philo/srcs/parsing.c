/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:13:42 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/05 15:16:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(int c);

int	parser(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("%s", WRONG_NB_ARG), EXIT_FAILURE);
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == 0)
			return (printf("%s", WRONG_FORMAT), EXIT_FAILURE);
		while (av[i][j])
			if (ft_isdigit(av[i][j++]) == EXIT_FAILURE)
				return (printf("%s", WRONG_FORMAT), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
