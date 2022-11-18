#include "philo.h"

void   philo_init(t_env *prog)
{
    /*init forks*/
    prog->forks = malloc(sizeof(pthread_mutex_t) * prog->inputs.no_of_philo);
    for (int i = 0; i < prog->inputs.no_of_philo; i++)
        pthread_mutex_init(&prog->forks[i], NULL);
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

void*    referee(void *prog)
{
    t_env   *cast;
    int     i;

    cast = (t_env*)prog;
    i = cast->thread_n;
    if (cast->inputs.eat_limit > 0) {
    /*We must run this for loop indefinite until death_flag == 1 or any philo reach eat_limit*/
        while (cast->death_flag == 0 && (cast->philos[i].no_of_ate < cast->inputs.eat_limit || cast->inputs.eat_limit == -1))
        {
            if (!check_philo_death(cast, &cast->philos[i]))
                break ;
            if (i + 1 == cast->inputs.no_of_philo)
                i = 0;
            else
                i++;
        }
    }
    /*in case optional args is not entered, it use this loop which run until any philo die*/
    else 
    {
        while (cast->death_flag == 0)
        {
            for (int j = 0; j < cast->inputs.no_of_philo; j++)
            {
                if (!check_philo_death(cast, &cast->philos[i]))
                    break ;
            }
        }
    }
    return (NULL);
}

void*   philo(void *prog)
{
    int     i;
    t_env   *use;

    use = (t_env*)prog;
    i = use->thread_n;
    while (use->death_flag == 0 && (use->philos[i].no_of_ate < use->inputs.eat_limit || use->inputs.eat_limit == -1))
    {
        /*I check if philo died, if yes this loop stop*/
        if (use->death_flag == 1)
            break ;
        /*The philo grab two forks*/
        use->philos[i].status = grab_fork;
        pthread_mutex_lock(&use->forks[use->philos[i].left_fork_index]);
        if (!check_and_print(*use, use->philos[i]))
            break ;
        pthread_mutex_lock(&use->forks[use->philos[i].right_fork_index]);
        if (!check_and_print(*use, use->philos[i]))
            break ;
        /*The philo start eating*/
        use->philos[i].status = eating;
        if (!check_and_print(*use, use->philos[i]))
            break ;
        usleep((use->inputs.eat_time) * 1000);
        /*The philo put two forks back to table*/
        pthread_mutex_unlock(&use->forks[use->philos[i].left_fork_index]);
        pthread_mutex_unlock(&use->forks[use->philos[i].right_fork_index]);
        use->philos[i].last_eat = get_ms();     
        use->philos[i].no_of_ate++;
        if (use->philos[i].no_of_ate == use->inputs.eat_limit)
            break ;
        /*The philo start sleeping*/
        use->philos[i].status = sleeping;
        if (!check_and_print(*use, use->philos[i]))
            break ;
        usleep((use->inputs.sleep_time) * 1000);
        /*When philo wake up, it start thinking*/
        use->philos[i].status = thinking;
        if (!check_and_print(*use, use->philos[i]))
            break ;
    }
    return (NULL);
}