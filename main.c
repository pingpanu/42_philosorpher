#include "philo.h"

t_input  get_input(int argc, char **argv)
{
    t_input ret;

    ret.no_of_philo = atoi(argv[1]);
    ret.die_time = atoi(argv[2]);
    ret.eat_time = atoi(argv[3]);
    ret.sleep_time = atoi(argv[4]);
    ret.eat_limit = -1;
    if (argc == 6)
        ret.eat_limit = atoi(argv[5]);
    return (ret);
}

int main(int argc, char **argv)
{
    t_env       prog;
    pthread_t   *th;
    pthread_t   refe;

    if (argc < 5 || argc > 6) {
        printf("You must type 4 or 5 arguments (exclude ./philo) \n");
        return (1);
    }
    prog.inputs = get_input(argc, argv);
    prog.death_flag = 0;
    /*make (no_of_philo) philos*/
    prog.philos = malloc(sizeof(t_philo_param) * prog.inputs.no_of_philo);
    philo_init(&prog);
    /*make (no_of_philo) philosorpher*/
    th = malloc(sizeof(pthread_t) * prog.inputs.no_of_philo);
    prog.start_time = get_ms();
    for (int i = 0; i < prog.inputs.no_of_philo; i++) {
        //printf("i = %d\n", i);
        prog.thread_n = i;
        if (pthread_create(&th[i], NULL, &philo, &prog) != 0) {
            printf("Failed to create thread philo[%d] \n", i + 1);
        }
        usleep(1000);
    }
    if (pthread_create(&refe, NULL, &referee, &prog) != 0) {
        printf("Failed to create referee\n");
    }
    /*join (no_of_philo) philosorpher*/
    for (int i = 0; i < prog.inputs.no_of_philo; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread philo[%d] \n", i + 1);
        }
    }
    if (pthread_join(refe, NULL) != 0) {
        printf("Failed to join refereee\n");
    }
    /*destroy all mutex to clean the program*/
    if (prog.death_flag == 1) {
        for (int i = 0; i < prog.inputs.no_of_philo; i++)
            pthread_mutex_destroy(&prog.forks[i]);
    }
    return (0);
}