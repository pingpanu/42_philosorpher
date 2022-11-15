#ifndef PHILOSORPHER_H
# define PHILOSORPHER_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum    e_state
{
    sleeping,
    eating,
    thinking,
    die,
}   t_state;

/*struct for main program*/
typedef struct s_observer {
    int no_of_philo; //number of philosorpher
    int die_time; //time from last meal that each philo can stay alive
    int eat_time; //time needed for each philo to eat
    int sleep_time; //time needed for each philo to sleep
    int no_of_ate; //times that each philosorpher had ate
    int died; //death flag, program will stop if died = 1
}   t_observer;

typedef struct s_philo_param
{
    t_observer              *ref;   //to pass argvs to philo
    int                     last_eat;   //to store last time it eat
    pthread_mutex_t         fork;   //each philo have a fork
    int                     fork_stat;  //status of the fork
    int                     philo_name;  //name of the philo
    struct s_philo_param    *next; //pointer to n+1 philo
}   t_philo_param;

void*   philo(t_philo_param *philo);
void   philo_init(t_philo_param *philo, t_observer obs);
void    philo_destroy(t_philo_param *philos);
#endif