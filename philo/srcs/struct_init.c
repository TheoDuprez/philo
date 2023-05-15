/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:41:22 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/08 15:15:54 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("%s", MALLOC_ERR), NULL);
	data->nb_philo = ft_atoi(av[1]);
	data->time_died = (ft_atoi(av[2]));
	data->time_eat = (ft_atoi(av[3]));
	data->time_sleep = (ft_atoi(av[4]));
	data->is_dead = 0;
	data->max_eat = -1;
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	if (!data->time_died || !data->time_eat || !data->time_sleep)
		return (printf("%s", WRONG_FORMAT), free(data), NULL);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (printf("%s", MALLOC_ERR), free(data), NULL);
	data->locked = malloc(sizeof(int) * data->nb_philo);
	if (!data->locked)
		return (printf("%s", MALLOC_ERR), free(data->fork), free(data), NULL);
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (printf("%s", MALLOC_ERR), ft_destroy_mutex(data), \
		ft_free_data(data), NULL);
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].fork_l = i;
		if (i == 0)
			philo[i].fork_r = data->nb_philo - 1;
		else
			philo[i].fork_r = i - 1;
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].eat_counter = 0;
		i++;
	}
	data->philo = philo;
	return (philo);
}
