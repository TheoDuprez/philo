/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:27:47 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/08 16:30:08 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_fork(t_data *data, t_philo *philo, int fork);

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (printf("%s", MUTEX_INIT_ERR), ft_free_data(data), EXIT_FAILURE);
	if (pthread_mutex_init(&data->exec, NULL) != 0)
		return (printf("%s", MUTEX_INIT_ERR), \
		pthread_mutex_destroy(&data->dead), ft_free_data(data), EXIT_FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			while (i >= 0)
				pthread_mutex_destroy(&data->fork[i--]);
			pthread_mutex_destroy(&data->exec);
			pthread_mutex_destroy(&data->dead);
			ft_free_data(data);
			return (printf("%s", MUTEX_INIT_ERR), EXIT_FAILURE);
		}
		data->locked[i++] = 0;
	}
	return (EXIT_SUCCESS);
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->exec);
	pthread_mutex_destroy(&data->dead);
}

inline int	wait_for_fork(t_data *data, t_philo *philo, int fork)
{
	while (check_fork(data, philo, fork) != 0)
	{
		if (philo->eat_counter != 0)
			if (check_if_time_to_die(philo) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (check_if_dead(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		usleep(250);
	}
	if (data->nb_philo == 1)
	{
		printf("%ld %d has taken a fork\n", ft_timing(philo), philo->id);
		usleep(data->time_died * 1000);
		printf("%ld %d is died\n", ft_timing(philo), philo->id);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&philo->data->fork[fork]);
	data->locked[fork] = 1;
	pthread_mutex_unlock(&philo->data->fork[fork]);
	return (EXIT_SUCCESS);
}

static int	check_fork(t_data *data, t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	if (data->locked[fork] == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[fork]);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->data->fork[fork]);
	return (EXIT_SUCCESS);
}

inline int	unlock_fork(t_data *data, t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	data->locked[fork] = 0;
	pthread_mutex_unlock(&philo->data->fork[fork]);
	return (EXIT_SUCCESS);
}
