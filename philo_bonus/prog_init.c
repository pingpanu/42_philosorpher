#include "philo.h"

void   philo_init(t_env *prog)
{
    for (int i = 0; i < prog->inputs.no_of_philo; i++)
    {
        prog->philos[i].philo_id = i + 1;
        prog->philos[i].last_eat = get_ms();
        prog->philos[i].no_of_ate = 0;
        prog->philos[i].left_fork_index = i;
        if (i == prog->inputs.no_of_philo - 1)
            prog->philos[i].right_fork_index = 0;
        else
            prog->philos[i].right_fork_index = i + 1;
    }
}

int     prog_sems_init(t_env *prog)
{
    sem_unlink("/forks");
    sem_unlink("/death");
    sem_unlink("/write");
    sem_unlink("/table");
    prog->sem_table = sem_open("/table", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if (prog->sem_table == SEM_FAILED) {
        printf("Failed to create 'master' semaphore\n");
        return (0);
    }
    prog->sem_dead = sem_open("/death", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if (prog->sem_dead == SEM_FAILED) {
        printf("Failed to create 'death' semaphore\n");
        return (0);
    }
    prog->sem_write = sem_open("/write", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if (prog->sem_write == SEM_FAILED) {
        printf("Failed to create 'write' semaphore\n");
        return (0);
    }
    prog->sem_forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, prog->inputs.no_of_philo);
    if (prog->sem_forks == SEM_FAILED) {
        printf("Failed to create 'forks' semaphore\n");
        return (0);
    }
    return (1);
}