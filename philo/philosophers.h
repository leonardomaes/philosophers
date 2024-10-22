/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:24:59 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/19 12:25:00 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

# define MAX_PHILOS 300

typedef struct s_philo
{
	pthread_t			philo;
	int					id;
	int					dead;
	size_t				start_time;
	size_t				time_to_die;
	size_t 				time_to_eat;
	size_t 				time_to_sleep;
	size_t 				times_eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	int					n_philos;
}				t_philo;

// PHILO UTILS
int			check_args(char **argv);
void		init_philos(t_philo *philos, char **argv, pthread_mutex_t *forks);
void		init_forks(pthread_mutex_t	*forks, int n);

// UTILS
int			ft_atoi(const char *nptr);
int			ft_isnum(char *str);
size_t		get_current_time(void);
int			ft_usleep(size_t milliseconds);

// ROUTINE
void		*is_dead(void	*philos);
int			start_routine(t_philo *philo);

#endif
