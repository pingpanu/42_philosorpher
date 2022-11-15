#include "philo.h"

void   philo_init(t_philo_param *philo, t_observer obs)
{
    struct timeval  cur_time;

    gettimeofday(&cur_time, NULL);
    for (int i = 0; i < obs.no_of_philo; i++) {
        philo[i].ref = &obs;
        philo[i].last_eat = 0; //suppose to be the time it create philo
        philo[i].philo_name = i + 1;
        philo[i].fork_stat = pthread_mutex_init(&philo[i].fork, NULL);
        if (philo[i].fork_stat != 0) {
            philo_destroy(philo);
            return (1);
        }
    }
    for (int j = 0; j < obs.no_of_philo; j++) {
        /*fill next pointer for each philo*/
        if (j == obs.no_of_philo - 1)
            philo[j].next = &philo[0];
        else
            philo[j].next = &philo[j + 1];
    }
}

void    philo_destroy(t_philo_param *philos)
{
    for (int i = 0; i < philos->ref->no_of_philo; i++)
        pthread_mutex_destroy(&philos[i].fork);
}

void*   philo(t_philo_param *philo)
{
    int     philo_hands[2]; //each philo have two hand to lock two forks and eat a meal
    int     time_passed; //this check how long time had passed
    t_philo_param   backup;

    if (time_passed > backup.ref->die_time) {
        printf("%d died\n", backup.philo_name);

    }
    backup = *philo;
    philo_hands[0] = pthread_mutex_lock(&backup.fork);
    philo_hands[1] = pthread_mutex_lock(&backup.next->fork);
    if (philo_hands[0] != 0 || philo_hands[1] != 0)
        printf("%d is thinking\n", backup.philo_name);
    else {
        printf("%d has taken a fork\n", backup.philo_name);
        printf("%d is eating\n", backup.philo_name);
    }
}