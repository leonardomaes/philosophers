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

void	*is_dead(void	*philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	int	i;
	while (1)
	{	//Talvez colocar um dlay para caso alterar a variavel start_time, de tempo de atualizar
		i = 0;
		while (i < philo[0].n_philos)
		{
			if (get_current_time() - philo[i].time_to_die >= philo[i].start_time)
			{
				philo[i].dead = 1;
				printf("%lu ms %i died\n", get_current_time() - philo[i].start_time, philo[i].id);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	start_routine(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &is_dead, philo) != 0)
		return 1;
	pthread_join(monitor, NULL);
	return (0);
}
