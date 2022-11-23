/*Utils is a collection of functions that keep appear in any progress.
Since philosophers can have severals bug, its important to track death_flag
throughout the function.*/

#include "philo.h"

/*this function check if death_flag == 1, if yes return 0, if not return 1*/
int    check_and_print(t_env prog, t_philo_param curr_philo)
{
    if (prog.death_flag == 1)
        return (0);
    if (curr_philo.status == grab_fork)
        printf("%lld %d has taken a fork\n", diff_ms(prog.start_time), curr_philo.philo_id);
    else if (curr_philo.status == eating)
        printf("%lld %d is eating\n", diff_ms(prog.start_time), curr_philo.philo_id);
    else if (curr_philo.status == sleeping)
        printf("%lld %d is sleeping\n", diff_ms(prog.start_time), curr_philo.philo_id);
    else if (curr_philo.status == thinking)
        printf("%lld %d is thinking\n", diff_ms(prog.start_time), curr_philo.philo_id);
    else if (curr_philo.status == die)
        printf("%lld %d died\n", diff_ms(prog.start_time), curr_philo.philo_id);
    if (prog.death_flag == 1)
        return (0);
    return (1);
}

/*this function is actually boolean function that check if any philo die
if yes, return 0 so the loop in referee stop*/
int     check_philo_death(t_env *prog, t_philo_param *curr_philo)
{   
    /*check if env death_flag = 1 (other philo died)
    if it is we stop whole process*/ 
    if (prog->death_flag == 1)
        return (0);
    if (diff_ms(curr_philo->last_eat) == prog->inputs.die_time) 
    {
        curr_philo->status = die;
        if (!check_and_print(*prog, *curr_philo))
            return (0);
        prog->death_flag = 1;
    }
    return (1);    
}

void*   death_check(void *prog)
{
    t_env   *rec;
    int     i;

    rec = (t_env*)prog;
    i = rec->thread_n;
    sem_wait(rec->sem_dead);
    if (diff_ms(rec->philos[i].last_eat) == rec->inputs.die_time) {
        rec->death_flag = 0;
        rec->philos[i].status = die;
        //sem_wait(rec->sem_write);
        printf("%lld %d died\n", diff_ms(rec->start_time), rec->philos[i].philo_id);
        //sem_post(rec->sem_write);
        sem_post(rec->sem_table);
    }
    sem_post(rec->sem_dead);
    return (NULL);
}

/*this function is for debugging*/
void    print_sem_value(sem_t *thesem, char *str)
{
    int     thesem_value;

    sem_getvalue(thesem, &thesem_value);
    printf("the sem_%s value = %d\n", str, thesem_value);
}