#include "philo.h"

void    clean_exit(t_env *prog, int no_of_philo)
{
    /*in case parent process detect death, it kill process*/
    if (no_of_philo != 0)
        kill_all_philos(prog, no_of_philo);
    /*always called*/
    sem_close(prog->sem_dead);
    sem_close(prog->sem_forks);
    sem_close(prog->sem_table);
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
        /*if no_of_philo reach zero due to it reach eat limit
        immediatly stop the program*/
        if (prog.inputs.no_of_philo == 0)
                clean_exit(&prog, 0);
        /*this is parent process to check all child processes (philos)
        if death detected, kill all child processes, if an philo reach eat
        limits, kill the philo and decrement no_of_philo*/
        for (int j = 0 ; j < prog.inputs.no_of_philo; j++) {
            
            waitpid(prog.philos[j].philo_pid, &status, 0);
            if (WEXITSTATUS(status) == 1)
                clean_exit(&prog, prog.inputs.no_of_philo);
            if (WEXITSTATUS(status) == 0) {
                kill(prog.philos[j].philo_pid, SIGKILL);
                prog.inputs.no_of_philo--;
            }
        }
    }
    return (0);
}