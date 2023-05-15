/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:15 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/09 14:48:40 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free_data(t_data *data)
{
	free(data->fork);
	free(data->locked);
	free(data);
}

void	ft_free_all(t_data *data, t_philo *philo, pthread_t *thd)
{
	free(philo);
	ft_free_data(data);
	free(thd);
}
