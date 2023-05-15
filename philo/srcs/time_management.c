/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:30:06 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/08 16:56:18 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_timing(t_philo *philo)
{
	return (actual_time() - philo->data->start_time);
}

long int	actual_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

inline int	ft_usleep(t_philo *philo, long int time_loop)
{
	while (actual_time() < time_loop)
	{
		if (check_if_time_to_die(philo) == 1)
			return (EXIT_FAILURE);
		if (check_if_dead(philo) == 1)
			return (EXIT_FAILURE);
		usleep(250);
	}
	return (EXIT_SUCCESS);
}

inline int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (EXIT_SUCCESS);
}

inline int	check_if_time_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if ((actual_time() - philo->last_eat) >= philo->data->time_died \
	&& philo->data->is_dead == 0)
	{
		usleep(1250);
		printf("%ld %d is died\n", ft_timing(philo), philo->id);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (EXIT_SUCCESS);
}
