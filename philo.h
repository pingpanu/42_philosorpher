#ifndef PHILOSORPHER_H
# define PHILOSORPHER_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <pthread.h>

/*struct for main program*/
typedef struct s_observer
{
    int no_of_philo; //number of philosorpher
    int die_time; //time from last meal that each philo can stay alive
    int eat_time; //time needed for each philo to eat
    int sleep_time; //time needed for each philo to sleep
    int no_of_ate; //times that each philosorpher had ate
}   t_observer;
#endif