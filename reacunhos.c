
/* void *computation(void *tab)
{
	t_philo *philo = (t_philo *) tab;

	pthread_mutex_lock(&philo->mutex);
	for (long i = 0; i < 10000000; i++)
	{
		philo->sum++;
	}
	pthread_mutex_unlock(&philo->mutex);
	printf("Add: %ld\n", philo->sum);
	return (NULL);
}

int	main()
{
	t_philo philo;
	pthread_t thread1;
	pthread_t thread2;

	philo.sum = 0;
	pthread_mutex_init(&philo.mutex, NULL);
	pthread_create(&thread1, NULL, computation, (void*)&philo);
	pthread_create(&thread2, NULL, computation, (void*)&philo);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&philo.mutex);
	return (0);
} */

/* int main() {
    struct timeval tv;
	struct timeval tz;
	struct timeval time;
	int	t;
	int	t2;

    if (gettimeofday(&tv, &tz) == 0) {
        printf("Segundos: %ld\n", tv.tv_sec);
        printf("Microsegundos: %ld\n", tv.tv_usec);
    } else {
        perror("gettimeofday");
    }
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	for (size_t i = 0; i < 1000000; i++)
	
	gettimeofday(&time, NULL);
	t2 = (t - (time.tv_sec * 1000 + time.tv_usec / 1000));
	printf("Time1 = %i\n", t);
	printf("diferenca = %i\n", t2);
    return 0;
}
 */