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

void	*is_dead(void *void_program)
{
	t_program *program;
	int	i;

	program = (t_program *)void_program;
	while (1)
	{
		ft_usleep(1);
		i = 0;
		while (i < program->philo[0].n_philos)
		{
			pthread_mutex_lock(program->philo[0].dead_lock);
			if (get_current_time() - program->philo[i].last_eat >= program->philo[i].time_to_die && program->philo[i].eating == 0)
			{
				printf("%lums %i died\n", get_current_time() - program->philo[i].start_time, program->philo[i].id);
				program->philo[i].dead = 1;
				program->dead = 1;
				pthread_mutex_unlock(program->philo[0].dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(program->philo[0].dead_lock);
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
	//pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	printf("%lums %i is eating\n", get_current_time() - philo->start_time, philo->id);
	philo->last_eat = get_current_time();
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	//pthread_mutex_unlock(philo->meal_lock);
}

void	*routine(void	*philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;

	while (check_dead(philo) == 0)
	{
		eat(philo);
	}
	return (NULL);
}
// Alerar toda a struct philo para dentro do overall, desta forma quando um filo morrer, altera a variavel do overall para parar todos os philos na funcao check_dead na routine

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
			return 1;
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < program->philo[0].n_philos)
	{
		pthread_join(program->philo[i].philo, NULL);
		i++;
	}
	program->dead = 2;
	return (0);
}
