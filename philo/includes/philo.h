/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:04:58 by tduprez           #+#    #+#             */
/*   Updated: 2023/05/09 15:11:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MALLOC_ERR "Error of malloc function\n"
# define WRONG_FORMAT "Wrong format detected in argument\n"
# define WRONG_NB_ARG "Wrong number of arguments\n"
# define MUTEX_INIT_ERR "Error in mutex init\n"

typedef struct s_philo
{
	int				id;
	int				fork_l;
	int				fork_r;
	int				eat_counter;
	long			last_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_eat;
	int				time_died;
	int				time_sleep;
	int				max_eat;
	int				is_dead;
	long			start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	exec;
	pthread_mutex_t	*fork;
	int				*locked;
	struct s_philo	*philo;
}	t_data;

//################## PROTOTYPE ##################//

/* parsing.c */
int			parser(int ac, char **av);

/* struct_init.c */

t_philo		*init_philo(t_data *data);
t_data		*init_data(int ac, char **av);

/* atoi.c */
int			ft_atoi(const char *str);

/* simulation.c */
int			exec_philo(t_data *data, pthread_t *thd);

/* philo_actions.c */
void		ft_actions(t_philo *philo, t_data *data);

/* free.c */
void		ft_free_data(t_data *data);
void		ft_free_all(t_data *data, t_philo *philo, pthread_t *thd);

/* mutex_management.c */
int			init_mutex(t_data *data);
void		ft_destroy_mutex(t_data *data);
int			unlock_fork(t_data *data, t_philo *philo, int fork);
int			wait_for_fork(t_data *data, t_philo *philo, int fork);

/* time_management.c */
long int	actual_time(void);
long int	ft_timing(t_philo *philo);
int			check_if_dead(t_philo *philo);
int			check_if_time_to_die(t_philo *philo);
int			ft_usleep(t_philo *philo, long int time_loop);

#endif
