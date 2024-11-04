/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:16:21 by lmaes             #+#    #+#             */
/*   Updated: 2024/11/04 13:16:22 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	phiosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_eat > time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	philosopher_full(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (philo->times_eat == philo->max_eat)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

void	*check_dead(void *void_program)
{
	int			i;
	int			count;
	t_program	*program;

	program = (t_program *)void_program;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < program->n_philos)
		{
			if (phiosopher_dead(&program->philo[i],
					program->philo[i].time_to_die)
				&& philosopher_full(&program->philo[i]) == 0)
			{
				printf("%lu %i died\n", get_current_time()
					- program->philo[i].start_time, program->philo[i].id);
				pthread_mutex_lock(program->philo[i].dead_lock);
				program->dead = 1;
				pthread_mutex_unlock(program->philo[i].dead_lock);
				return (NULL);
			}
			if (philosopher_full(&program->philo[i]))
				count++;
			i++;
		}
		if (count == program->n_philos)
		{
			program->finished = 1;
			return (NULL);
		}
	}
	return (NULL);
}
