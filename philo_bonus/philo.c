#include "philo.h"

static void     philo_sleepthink(t_env *prog, int i)
{
    //the philo is sleeping
    prog->philos[i].status = sleeping;
    printf("%lld %d is sleeping\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
    usleep(prog->inputs.sleep_time * 1000);
    //the philo wake up and thinking
    prog->philos[i].status = thinking;
    printf("%lld %d is thinking\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
}

static void     philo_eating(t_env *prog, int i)
{
    prog->philos[i].status = eating;
    printf("%lld %d is eating\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
    usleep(prog->inputs.eat_time * 1000);
    sem_post(prog->sem_forks);
    sem_post(prog->sem_forks);
    prog->philos[i].last_eat = get_ms();
    prog->philos[i].no_of_ate++;
}

static void     philo_grabforks(t_env *prog, int i)
{
    prog->philos[i].status = grab_fork;
    sem_wait(prog->sem_forks);
    printf("%lld %d has taken a fork\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
    sem_wait(prog->sem_forks);
    printf("%lld %d has taken a fork\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
}

void   philo(t_env *prog)
{
    int     i;

    i = prog->thread_n;
    pthread_create(&(prog->philos[i].monitor), NULL, monitor, prog);
    while (1) {
        philo_grabforks(prog, i);
        philo_eating(prog, i);
        if (prog->philos[i].no_of_ate == prog->inputs.eat_limit)
            exit(0);
        philo_sleepthink(prog, i);
    }
}