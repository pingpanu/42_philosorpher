#include "philo.h"

void*   philo(int i)
{
    if (time > obs.die_time)
    {
        printf("%d %d died\n", time, i + 1);
        obs.died = 1;
    }
    pthread_mutex_lock(&forks[i]);
    pthread_mutex_lock(&forks[(i + 1) % obs.no_of_philo]);
    /*if philo can't lock two mutexes*/
        printf("%d %d is thinking\n", time, i + 1);
    printf("%d %d has taken a fork\n", time, i + 1);
    printf("%d %d is eating\n", time, i + 1);
    usleep(obs.eat_time);
    printf("%d %d is sleeping\n", time, i + 1);
    usleep(obs.sleep_time);
}