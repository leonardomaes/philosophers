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
	int				id;
	size_t					start_time;
	size_t				time_to_die;
	size_t 				time_to_eat;
	size_t 				time_to_sleep;
	size_t 				must_eat;
}				t_philo;

// PHILO UTILS
int			check_args(char **argv);
t_philo		*init_philos(char **argv);


// UTILS
int			ft_atoi(const char *nptr);
int			ft_isnum(char *str);
size_t		get_current_time(void);

#endif
