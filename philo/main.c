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

/* void *computation(void *nbr)
{
	long *number = (long*)nbr;
	printf("nbr = %ld\n", *number);
	return (NULL);
} */

void *computation(void *add)
{
	long sum = 0;
	long *add_num = (long *) (add);

	for (long i = 0; i < 1000000000; i++)
		sum += *add_num;
	printf("Add: %ld\n", *add_num);
	return (NULL);
}

int	main()
{
	long n1 = 1;
	long n2 = 2;

	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1, NULL, computation, (void*)&n1);
	pthread_create(&thread2, NULL, computation, (void*)&n2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return (0);
}
