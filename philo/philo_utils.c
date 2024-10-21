/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
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

t_philo	*init_philos(char **argv)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		philo[i].start_time = get_current_time();
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		i++;
	}
	return (philo);
} 
