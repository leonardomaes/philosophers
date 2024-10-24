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
	if (get_current_time() - philo->last_eat > time_to_die /*&& philo->eating == 0*/)
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
		//ft_usleep(1);
		i = 0;
		while (i < program->philo[0].n_philos)
		{		// Problema na condicao quando o eating estiver 1 ou 0
			if (phiosopher_dead(&program->philo[i], program->philo[i].time_to_die))		// && program->philo[i].eating == 0
			{
				pthread_mutex_lock(program->philo[i].dead_lock);
				printf("%lums %i died\n", get_current_time() - program->philo[i].start_time, program->philo[i].id);
				program->philo[i].dead = 1;
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
	if (philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	printf("%lums %i is eating\n", get_current_time() - philo->start_time, philo->id);		//possivel erro na mutex aqui
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

void	*routine(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;

	while (check_dead(philo) == 0)
	{
		//ft_usleep(1);
		eat(philo);
	}
	return (NULL);
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
	pthread_join(monitor, NULL);
	i = 0;
	while (i < program->philo[0].n_philos)
	{
		if (pthread_join(program->philo[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	//program->dead = 2;
	return (0);
}
