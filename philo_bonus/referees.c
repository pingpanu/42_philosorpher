#include "philo.h"

void*    referee1(void *prog)
{
    t_env   *cast;
    int     i;

    cast = (t_env*)prog;
    i = cast->thread_n;
    if (cast->inputs.eat_limit > 0) {
    /*We must run this for loop indefinite until death_flag == 1 or any philo reach eat_limit*/
        while (cast->death_flag == 0 && (cast->eat_end == 0 || cast->inputs.eat_limit == -1))
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

void*   referee2(void *prog)
{
        t_env   *cast;
    int     i;

    cast = (t_env*)prog;
    i = cast->thread_n;
    while (cast->death_flag == 0 && (cast->eat_end == 0 || cast->inputs.eat_limit == -1))
    {
        if (cast->death_flag == 1)
            break ;
        if (cast->philos[i].no_of_ate == cast->inputs.eat_limit) {
            if (cast->death_flag == 1)
                break ;
            cast->eat_end = 1;
        }
        if (i + 1 == cast->inputs.no_of_philo)
            i = 0;
        else
            i++;
    }
    return (NULL);
}