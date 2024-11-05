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

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*tmp_r;
	pthread_mutex_t	*tmp_l;

	tmp_r = philo->r_fork;
	tmp_l = philo->l_fork;
	if (philo->id % 2 == 1)
	{
		tmp_r = philo->l_fork;
		tmp_l = philo->r_fork;
	}
	pthread_mutex_lock(tmp_r);
	if (is_dead(philo) == 0)
		printf("%lu %i has taken a fork\n", get_current_time()
			- philo->start_time, philo->id);
	if (philo->n_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(tmp_r);
		return ;
	}
	pthread_mutex_lock(tmp_l);
	if (is_dead(philo) == 0)
		printf("%lu %i has taken a fork\n", get_current_time()
			- philo->start_time, philo->id);
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*tmp_r;
	pthread_mutex_t	*tmp_l;

	printf("%lu %i is eating\n", get_current_time() - philo->start_time,
		philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_eat = get_current_time();
	philo->times_eat++;
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 1;
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	tmp_r = philo->r_fork;
	tmp_l = philo->l_fork;
	if (philo->id % 2 == 1)
	{
		tmp_r = philo->l_fork;
		tmp_l = philo->r_fork;
	}
	pthread_mutex_unlock(tmp_l);
	pthread_mutex_unlock(tmp_r);
}

int	sleepwalker(t_philo *philo)
{
	if (is_dead(philo) == 1)
		return (1);
	printf("%lu %i is sleeping\n", get_current_time() - philo->start_time,
		philo->id);
	ft_usleep(philo->time_to_sleep);
	if (is_dead(philo) == 1)
		return (1);
	printf("%lu %i is thinking\n", get_current_time() - philo->start_time,
		philo->id);
	return (0);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

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
		if (*philo->finished == 1)
			break ;
		if (sleepwalker(philo) == 1)
			return (NULL);
		if (philo->times_eat == philo->max_eat)
			break ;
	}
	return (NULL);
}

int	start_routine(t_program *program)
{
	int			i;
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &check_dead, program);
	i = 0;
	while (i < program->n_philos)
	{
		pthread_create(&program->philo[i].philo, NULL, &routine,
			&program->philo[i]);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < program->n_philos)
	{
		pthread_join(program->philo[i].philo, NULL);
		i++;
	}
	return (0);
}
