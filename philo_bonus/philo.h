#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <ctype.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef enum    e_state
{
    sleeping,
    grab_fork,
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

/*struct for each philosorphers
for bonus, philosopher is child
process controled by parent process*/
typedef struct s_philo_param
{
    t_state         status;
    pthread_t       monitor; // thread to check if the philo die
    pid_t           philo_pid; //process id of each philo
    long long       last_eat;   //to store last time it eat
    int             philo_id;  //name of the philo
    int             no_of_ate; //times that each philosorpher had ate
    int             left_fork_index; //actually philo's left hand
    int             right_fork_index; //actually philo's right hand
}   t_philo_param;

/*struct for whole program
for bonus, main.c is parent process while
anything regarding philosopher (like routine)
are child processes*/
typedef struct  s_env
{
    sem_t           *sem_forks; //number of forks on table
    //sem_t           *sem_write; //check printf
    sem_t           *sem_dead; //check if philo died
    sem_t           *sem_table; //master semaphore to stop process
    t_input         inputs;
    t_philo_param   *philos;
    pthread_t       deathstop;
    pthread_t       limitstop;
    int             death_flag;
    //int             eat_end;
    int             thread_n;
    long long       start_time;
}   t_env;

/*in input.c, to check input*/
int     valid_arguments(int argc, char **argv, t_env *prog);
/*in prog_init.c to initiate prog*/
int     prog_sems_init(t_env *prog);
void        philo_init(t_env *prog);
/*in philo.c, to execute processes*/
void        philo(t_env *prog);
/*in microsecond.c, to get time in millisecond*/
long long   get_ms(void);
long long   diff_ms(long long time);
/*in utils.c, to check and kill process in philo.c*/
void*   monitor(void *prog);
void    kill_all_philos(t_env *prog, int no_of_philo);
#endif