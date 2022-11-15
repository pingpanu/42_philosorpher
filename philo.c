#include "philo.h"

void   philo_init(t_philo_param *philo, t_observer obs, int i)
{
    struct timeval  cur_time;

    gettimeofday(&cur_time, NULL);
    philo->ref = &obs;
    philo->last_eat = 0;
    philo->philo_num = i;
    philo->fork_stat = pthread_mutex_init(&philo->fork, NULL);
}

void    philo_destroy(t_philo_param *philos)
{
    for (int i = 0; i < philos->ref->no_of_philo; i++)
        pthread_mutex_destroy(&philos[i].fork);
}

void*   philo(void *philos)
{
}