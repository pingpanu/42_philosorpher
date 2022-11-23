#include "philo.h"

void    clean_exit(t_env *prog)
{
    for (int i = 0; i < prog->inputs.no_of_philo; i++)
        kill(prog->philos[i].philo_pid, SIGKILL);
    sem_close(prog->sem_dead);
    sem_close(prog->sem_forks);
    sem_close(prog->sem_table);
    sem_close(prog->sem_write);
    free(prog->philos);
}

int main(int argc, char **argv)
{
    t_env       prog;

    if (!valid_arguments(argc, argv, &prog))
        return (1);
    if (!prog_sems_init(&prog))
        return (1);
    philo_init(&prog);
    prog.start_time = get_ms();
    /*pthread_create(&prog.deathstop, NULL, &referee1, &prog);
    pthread_join(prog.deathstop, NULL);
    if (prog.inputs.eat_limit > 0) {
        pthread_create(&prog.limitstop, NULL, &referee2, &prog);      
        pthread_join(prog.limitstop, NULL);  
    }*/
    sem_wait(prog.sem_table);
    for (int i = 0; i < prog.inputs.no_of_philo; i++)
    {
        prog.thread_n = i;
        philo(&prog);
        usleep(1000);
    }
    clean_exit(&prog);
    return (0);
}