#include "philo.h"

void   philo(t_env *prog)
{
    int     i;

    i = prog->thread_n;
    prog->philos[i].philo_id = fork();
    if (prog->philos[i].philo_id == 0)
    {
        /*pthread_create(&prog->philos[i].philodied, NULL, &death_check, &prog);
        pthread_join(prog->philos[i].philodied, NULL);*/
        while (prog->death_flag == 0 && prog->eat_end == 0) {
            /*the philo grab two forks*/
            //sem_wait(prog->sem_table);
            prog->philos[i].status = grab_fork;
            sem_wait(prog->sem_forks);
            printf("%lld %d has taken a fork\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
            sem_wait(prog->sem_forks);
            printf("%lld %d has taken a fork\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
            /*the philo is eating*/
            prog->philos[i].status = eating;
            printf("%lld %d is eating\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
            usleep(prog->inputs.eat_time * 1000);
            /*the philo finish eating and put two forks back to table*/
            print_sem_value(prog->sem_forks, "forks");
            sem_post(prog->sem_forks);
            sem_post(prog->sem_forks);
            print_sem_value(prog->sem_forks, "forks");
            prog->philos[i].last_eat = get_ms();
            prog->philos[i].no_of_ate++;
            /*the philo is sleeping*/
            prog->philos[i].status = sleeping;
            printf("%lld %d is sleeping\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
            usleep(prog->inputs.sleep_time * 1000);
            /*the philo wake up and thinking*/
            prog->philos[i].status = thinking;
            printf("%lld %d is thinking\n", diff_ms(prog->start_time), prog->philos[i].philo_id);
        }
        sem_post(prog->sem_table);
    }
}