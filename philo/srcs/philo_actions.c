/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:05:09 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/08 17:08:08 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static inline int	eating(t_philo *philo);
static inline int	sleeping(t_philo *philo);
static inline int	thinking(t_philo *philo);

void	ft_actions(t_philo *philo, t_data *data)
{
	while (data->max_eat != philo->eat_counter)
	{
		if (check_if_dead(philo) == 1)
			return ;
		if (wait_for_fork(data, philo, philo->fork_l) == 1)
			return ;
		if (wait_for_fork(data, philo, philo->fork_r) == 1)
			return ;
		if (eating(philo) == 1)
			return ;
		unlock_fork(data, philo, philo->fork_l);
		unlock_fork(data, philo, philo->fork_r);
		if (check_if_dead(philo) == 1)
			return ;
		if (sleeping(philo) == 1)
			return ;
		if (check_if_dead(philo) == 1)
			return ;
		philo->eat_counter++;
	}
}

static inline int	eating(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (EXIT_FAILURE);
	if (philo->eat_counter != 0)
		if (check_if_time_to_die(philo) == 1)
			return (EXIT_FAILURE);
	philo->last_eat = actual_time();
	if (check_if_time_to_die(philo) == 1)
		return (EXIT_FAILURE);
	if (check_if_dead(philo) == 1)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->data->exec);
	if (check_if_dead(philo) == 1)
		return (pthread_mutex_unlock(&philo->data->exec), EXIT_FAILURE);
	printf("%ld %d has taken a fork\n", ft_timing(philo), philo->id);
	printf("%ld %d has taken a fork\n", ft_timing(philo), philo->id);
	printf("%ld %d is eating\n", ft_timing(philo), philo->id);
	pthread_mutex_unlock(&philo->data->exec);
	if (ft_usleep(philo, (philo->last_eat + philo->data->time_eat)))
		return (EXIT_FAILURE);
	if (check_if_time_to_die(philo) == 1)
		return (EXIT_FAILURE);
	if (check_if_dead(philo) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static inline int	sleeping(t_philo *philo)
{
	if (check_if_time_to_die(philo) == 1)
		return (EXIT_FAILURE);
	if (check_if_dead(philo) == 1)
		return (EXIT_FAILURE);
	printf("%ld %d is sleeping\n", ft_timing(philo), philo->id);
	if (ft_usleep(philo, actual_time() + (philo->data->time_sleep)))
		return (EXIT_FAILURE);
	thinking(philo);
	return (EXIT_SUCCESS);
}

static inline int	thinking(t_philo *philo)
{
	if (check_if_time_to_die(philo) == 1)
		return (EXIT_FAILURE);
	if (check_if_dead(philo) == 1)
		return (EXIT_FAILURE);
	printf("%ld %d is thinking\n", ft_timing(philo), philo->id);
	if (check_if_time_to_die(philo) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
