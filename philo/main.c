/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:24:19 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/19 12:24:20 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_philos(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	i = 0;
	while (i < program->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_program		program;
	pthread_mutex_t	*forks;
	int				n;

	if (argc != 5 && argc != 6)
		return (write(2, "Incorret arguments\n", 19), 1);
	if (check_args(argv) == 1)
		return (1);
	n = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo) * n);
	forks = malloc(sizeof(pthread_mutex_t) * n);
	init_forks(forks, n);
	init_program(&program, philos, forks, argv);
	if (philos == NULL)
		return (1);
	if (start_routine(&program) == 1)
	{
		destroy_philos(&program, forks);
		free(forks);
		free(philos);
		return (1);
	}
	destroy_philos(&program, forks);
	free(forks);
	free(philos);
	return (0);
}
