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
	int					eating;
	size_t				start_time;
	size_t				last_eat;
	size_t				time_to_die;
	size_t 				time_to_eat;
	size_t 				time_to_sleep;
	size_t 				times_eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	int					n_philos;
}				t_philo;

typedef struct s_program
{
	int					dead;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philo;
}				t_program;


// init
int			check_args(char **argv);
void		init_philos(t_philo *philo, char **argv, pthread_mutex_t *forks, t_program	*program);
void		init_forks(pthread_mutex_t	*forks, int n);
void		init_program(t_program	*program);
// UTILS
int			ft_atoi(const char *nptr);
int			ft_isnum(char *str);
size_t		get_current_time(void);
int			ft_usleep(size_t milliseconds);

// ROUTINE
void		*routine(void	*philos);
int			start_routine(t_philo *philo, t_program *program);

#endif
