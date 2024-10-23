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

void	destroy_philos(t_philo *philo, pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[n]);
		i++;
	}
	free(forks);
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_philo 			*philos;
	t_program			program;
	pthread_mutex_t 	*forks;				//Inicializar os garfos fora da struct
	int					n;


	size_t				start;				// Trash
	start = get_current_time();				// Trash


	if (argc != 5 && argc != 6)
		return (write(2, "Incorret arguments\n", 19), 1);
	if (check_args(argv) == 1)
		return (1);
	n = ft_atoi(argv[1]);
	philos = malloc(sizeof(t_philo) * n);
	forks = malloc(sizeof(pthread_mutex_t) * n);



	init_forks(forks, n);
	init_program(&program);
	init_philos(philos, argv, forks, &program);
	if (philos == NULL)
		return (1);
	if (start_routine(philos, &program) == 1)
	{
		pthread_mutex_destroy(&program.dead_lock);
		pthread_mutex_destroy(forks);
		free(forks);
		free(philos);
		return (1);
	}

	pthread_mutex_destroy(&program.dead_lock);
	pthread_mutex_destroy(forks);
	free(forks);
	free(philos);
	return (0);
}


	/*for (int i = 0; i < ft_atoi(argv[1]); i++)		// Trash
	{
		printf("-->Philo %i:\ndie:   %zu\neat:   %zu\nsleep: %zu\n", i + 1, philos[i].time_to_die, philos[i].time_to_eat, philos[i].time_to_sleep);
	}
	printf("Time_philo 1 = %zu\n", get_current_time() - philos[0].start_time);		// Trash
	printf("Time_program = %zu\n", get_current_time() - start);		// Trash*/