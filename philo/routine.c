/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:00 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/21 14:18:01 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		phiosopher_dead(t_philo *philo, size_t	time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_eat >= time_to_die && philo->eating == 0)		// Possivel
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

void	*is_dead(void *void_program)
{
	t_program *program;
	int	i;

	program = (t_program *)void_program;
	while (1)
	{
		i = 0;
		while (i < program->philo[0].n_philos)
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

int	check_dead(t_philo *philo)
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

void	*routine(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_dead(philo) == 0)
	{
		eat(philo);
		printf("%lums %i is sleeping\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_sleep);
	}
	return (NULL);
}

void	eat(t_philo *philo)		// Need to be fixed
{
	pthread_mutex_lock(philo->r_fork);
	printf("%lums Philo %i took -> fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("%lums Philo %i took <- fork\n", get_current_time() - philo->start_time, philo->id);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	printf("%lums %i is eating\n", get_current_time() - philo->start_time, philo->id);
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	start_routine(t_program *program)
{
	pthread_t	monitor;
	int	i;

	i = 0;
	if (pthread_create(&monitor, NULL, &is_dead, program) != 0)
		return (1);
	while (i < program->philo[0].n_philos)
	{
		if (pthread_create(&program->philo[i].philo, NULL, &routine, &program->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	i = 0;
	while (i < program->philo[0].n_philos)
	{
		if (pthread_join(program->philo[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
