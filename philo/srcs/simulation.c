/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:06:37 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/09 14:58:48 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*routine(void *arg);

int	exec_philo(t_data *data, pthread_t *thd)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->exec);
	while (i < data->nb_philo)
	{
		if (pthread_create(&thd[i], NULL, &routine, &data->philo[i]) != 0)
			return (printf("Error in pthread_create\n"), \
			pthread_mutex_unlock(&data->exec), EXIT_FAILURE);
		i++;
	}
	i = 0;
	data->start_time = actual_time();
	pthread_mutex_unlock(&data->exec);
	while (i < data->nb_philo)
	{
		if (pthread_join(thd[i], NULL) != 0)
			return (printf("Error in pthread_join\n"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	pthread_mutex_lock(&data->exec);
	pthread_mutex_unlock(&data->exec);
	if (philo->id % 2 == 0 && data->max_eat != 0)
	{
		printf("%ld %d is thinking\n", ft_timing(philo), philo->id);
		usleep(50000);
	}
	else if (philo->id == philo->data->nb_philo && \
	philo->data->nb_philo % 2 != 0 && philo->data->nb_philo != 1)
	{
		printf("%ld %d is thinking\n", ft_timing(philo), philo->id);
		usleep(1500);
	}
	ft_actions(philo, data);
	return (NULL);
}
