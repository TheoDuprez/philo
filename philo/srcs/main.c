/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:05:53 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/09 14:49:09 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*thd;

	if (parser(ac, av))
		return (EXIT_FAILURE);
	data = init_data(ac, av);
	if (!data)
		return (EXIT_FAILURE);
	if (init_mutex(data))
		return (EXIT_FAILURE);
	philo = init_philo(data);
	if (!philo)
		return (EXIT_FAILURE);
	thd = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thd)
		return (printf("%s", MALLOC_ERR), ft_destroy_mutex(data), \
		ft_free_data(data), free(philo), EXIT_FAILURE);
	exec_philo(data, thd);
	ft_destroy_mutex(data);
	ft_free_all(data, philo, thd);
	return (EXIT_SUCCESS);
}
