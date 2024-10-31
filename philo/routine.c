/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:38:33 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/30 11:38:34 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		phiosopher_dead(t_philo *philo, size_t	time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_eat >= time_to_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

void	*check_dead(void *void_program)
{
	int	i;
	t_program *program;

	program = (t_program *)void_program;
	while (1)
	{
		i = 0;
		while (i < program->n_philos)
		{
			if (phiosopher_dead(&program->philo[i], program->philo[i].time_to_die))
			{
				printf("%lums %i died\n", get_current_time() - program->philo[i].start_time, program->philo[i].id);
				pthread_mutex_lock(program->philo[i].dead_lock);
				program->dead = 1;
				pthread_mutex_unlock(program->philo[i].dead_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

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

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	if (is_dead(philo) == 0)
		printf("%lums Philo %i has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		if (is_dead(philo) == 0)
			printf("%lums Philo %i has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		if (is_dead(philo) == 0)
			printf("%lums Philo %i has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	}
}

void	eat(t_philo *philo)
{

	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	printf("%lums %i is eating\n", get_current_time() - philo->start_time, philo->id);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}


void	*routine(void	*void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;

	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (is_dead(philo) == 0)
	{
		if (is_dead(philo) == 1)
			return (NULL);
		take_forks(philo);
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (NULL);
		}
		eat(philo);
		if (is_dead(philo) == 1)
			return (NULL);
		printf("%lums %i is sleeping\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_sleep);
		if (is_dead(philo) == 1)
			return (NULL);
		printf("%lums %i is thinking\n", get_current_time() - philo->start_time, philo->id);
	}
	return (NULL);
}

int	start_routine(t_program *program)
{
	int	i;
	pthread_t   monitor;

	if (pthread_create(&monitor, NULL, &check_dead, program) != 0)
		return (1);
	i = 0;
	while (i < program->n_philos)
	{
		if (pthread_create(&program->philo[i].philo, NULL, &routine, &program->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	i = 0;
	while (i < program->n_philos)
	{
		if (pthread_join(program->philo[i].philo, NULL) != 0)
			return (1);
		//pthread_detach(program->philo[i].philo);
		i++;
	}
	
	return (0);
}