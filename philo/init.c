/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:43:01 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/21 12:43:02 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| ft_isnum(argv[1]) == 1)
		return (write(2, "Invalid philosophers\n", 22), 1);
	if (ft_atoi(argv[2]) <= 60 || ft_isnum(argv[2]) == 1)
		return (write(2, "Invalid Time to die\n", 20), 1);
	if (ft_atoi(argv[3]) <= 60 || ft_isnum(argv[3]) == 1)
		return (write(2, "Invalid Time to eat\n", 20), 1);
	if (ft_atoi(argv[4]) <= 60 || ft_isnum(argv[4]) == 1)
		return (write(2, "Invalid Time to sleep\n", 22), 1);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0 || ft_isnum(argv[5]) == 1)
		{
			write(2, "Invalid number\n", 15);
			return (1);
		}
	}
	return (0);
}

void	init_forks(pthread_mutex_t	*forks, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(forks, NULL);
		i++;
	}
}

void	init_program(t_program	*program)
{
	program->dead = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_philos(t_philo *philo, char **argv, pthread_mutex_t *forks, t_program	*program)
{
	int		i;

	i = 0;
	
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].start_time = get_current_time();
		philo[i].last_eat = get_current_time();
		philo[i].dead = 0;
		philo[i].eating = 0;
		philo[i].n_philos = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}
