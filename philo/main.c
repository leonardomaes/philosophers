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

void	destroy_philos(t_philo *philo)
{
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_philo *philos;
	size_t	start;		// Trash

	start = get_current_time();		// Trash
	if (argc != 5 && argc != 6)
	{
		write(2, "Incorret arguments\n", 19);
		return (1);
	}
	if (check_args(argv) == 1)
		return (1);
	philos = init_philos(argv);
	if (philos == NULL)
		return (1);


	for (int i = 0; i < ft_atoi(argv[1]); i++)		// Trash
	{
		printf("-->Philo %i:\ndie:   %zu\neat:   %zu\nsleep: %zu\n", i + 1, philos[i].time_to_die, philos[i].time_to_eat, philos[i].time_to_sleep);
	}
	printf("Time_philo 1 = %zu\n", get_current_time() - philos[0].start_time);		// Trash
	destroy_philos(philos);
	printf("Time_program = %zu\n", get_current_time() - start);		// Trash
	return (0);
}
