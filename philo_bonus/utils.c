/*Utils is a collection of functions that keep appear in any progress.
Since philosophers can have severals bug, its important to track death_flag
throughout the function.*/

#include "philo.h"

void*   monitor(void *prog)
{
    t_env   *rec;
    int     i;

    rec = (t_env*)prog;
    i = rec->thread_n;
    while (1)
    {
        sem_wait(rec->sem_dead);
        if (diff_ms(rec->philos[i].last_eat) == rec->inputs.die_time) {
            rec->philos[i].status = die;
            printf("%lld %d died\n", diff_ms(rec->start_time), rec->philos[i].philo_id);
            rec->death_flag = 1;
            exit(1);
        }
        sem_post(rec->sem_dead);
    }
    return (NULL);
}

void kill_all_philos(t_env *prog, int no_of_philo)
{
    for (int i = 0; i < no_of_philo; i++)
    {
        if (prog->philos[i].philo_pid != 0)
            kill(prog->philos[i].philo_pid, SIGKILL);
    }
    free (prog->philos);
}