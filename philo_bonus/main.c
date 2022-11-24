#include "philo.h"

void    clean_exit(t_env *prog)
{
    int     status;

    for (int i = 0; i < prog->inputs.no_of_philo; i++)
        waitpid(prog->philos[i].philo_pid, &status, 0);
    sem_close(prog->sem_dead);
    sem_close(prog->sem_forks);
    //sem_close(prog->sem_table);
    //sem_close(prog->sem_write);
    free(prog->philos);
    exit(0);
}

int main(int argc, char **argv)
{
    t_env   prog;
    int     status;

    if (!valid_arguments(argc, argv, &prog))
        return (1);
    if (!prog_sems_init(&prog))
        return (1);
    prog.start_time = get_ms();

    philo_init(&prog);
    while (1)
    {
        waitpid(0, &status, 0);
        if (WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == 1)
            clean_exit(&prog);
    }
    return (0);
}