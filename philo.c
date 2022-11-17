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
            if (diff_ms(cast->philos[i].last_eat) == cast->inputs.die_time) {
                if (cast->death_flag == 1)
                    break ;
                printf("%lld %d died\n", diff_ms(cast->start_time), cast->philos[i].philo_id);
                cast->death_flag = 1;
            }
            if (i + 1 == cast->inputs.no_of_philo)
                i = 0;
            else
                i++;
        }
    }
    else 
    {
        while (cast->death_flag == 0)
        {
            for (int j = 0; j < cast->inputs.no_of_philo; j++)
            {
                if (diff_ms(cast->philos[j].last_eat) == cast->inputs.die_time) {
                    if (cast->death_flag == 1)
                        break ;
                    printf("%lld %d died\n", diff_ms(cast->start_time), cast->philos[j].philo_id);
                    cast->death_flag = 1;
                }
            }
        }
    }
    return (NULL);
}

void*   philo(void *prog)
{
    //t_state status;
    int     i;
    t_env   *use;

    use = (t_env*)prog;
    i = use->thread_n;
    //printf("i = %d\n", i);
    while (use->death_flag == 0 && (use->philos[i].no_of_ate < use->inputs.eat_limit || use->inputs.eat_limit == -1))
    {
        if (use->death_flag == 1)
            break ;
        pthread_mutex_lock(&use->forks[use->philos[i].left_fork_index]);
        if (use->death_flag == 1)
            break ;
        printf("%lld %d has taken a fork\n", diff_ms(use->start_time), use->philos[i].philo_id);
        if (use->death_flag == 1)
            break ;
        pthread_mutex_lock(&use->forks[use->philos[i].right_fork_index]);
        if (use->death_flag == 1)
            break ;
        printf("%lld %d has taken a fork\n", diff_ms(use->start_time), use->philos[i].philo_id);
        if (use->death_flag == 1)
            break ;
        printf("%lld %d is eating\n", diff_ms(use->start_time), use->philos[i].philo_id);
        if (use->death_flag == 1)
            break ;
        usleep((use->inputs.eat_time) * 1000);
        pthread_mutex_unlock(&use->forks[use->philos[i].left_fork_index]);
        pthread_mutex_unlock(&use->forks[use->philos[i].right_fork_index]);
        use->philos[i].last_eat = get_ms();     
        use->philos[i].no_of_ate++;
        //status = sleeping;
        if (use->death_flag == 1)
            break ;
        printf("%lld %d is sleeping\n", diff_ms(use->start_time), use->philos[i].philo_id);
        if (use->death_flag == 1)
            break ;
        usleep((use->inputs.sleep_time) * 1000);
        if (use->death_flag == 1)
            break ;
        printf("%lld %d is thinking\n", diff_ms(use->start_time), use->philos[i].philo_id);
        if (use->death_flag == 1)
            break ;
    }
    return (NULL);
}