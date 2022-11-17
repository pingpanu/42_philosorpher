#ifndef PHILOSORPHER_H
# define PHILOSORPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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

/*struct to store input*/
typedef struct s_input {
    int no_of_philo; //number of philosorpher
    int die_time; //time from last meal that each philo can stay alive
    int eat_time; //time needed for each philo to eat
    int sleep_time; //time needed for each philo to sleep
    int eat_limit; //optional arguments to stop program when any philo eat to this number
}   t_input;

/*struct for each philosorphers*/
typedef struct s_philo_param
{
    //t_state         status;
    long long       last_eat;   //to store last time it eat
    int             philo_id;  //name of the philo
    int             no_of_ate; //times that each philosorpher had ate
    int             left_fork_index; //actually philo's left hand
    int             right_fork_index; //actually philo's right hand
}   t_philo_param;

/*struct for whole program*/
typedef struct  s_env
{
    t_input         inputs;
    t_philo_param   *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t *write;
    int             death_flag;
    int             thread_n;
    long long       start_time;
}   t_env;

void*       philo(void *prog);
void*       referee(void *prog);
void        philo_init(t_env *prog);
long long   get_ms(void);
long long   diff_ms(long long time);
#endif