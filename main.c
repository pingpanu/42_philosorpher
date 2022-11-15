#include "philo.h"

t_observer  get_obs(int argc, char **argv)
{
    t_observer  ret;

    ret.died = 0;
    ret.no_of_philo = atoi(argv[1]);
    ret.die_time = atoi(argv[2]);
    ret.eat_time = atoi(argv[3]);
    ret.sleep_time = atoi(argv[4]);
    if (argc == 6)
        ret.no_of_ate = atoi(argv[5]);
    return (ret);
}

int main(int argc, char **argv)
{
    t_observer  obs;
    t_philo_param   *philos;
    pthread_t  *th;

    if (argc < 5 || argc > 6) {
        printf("You must type 4 or 5 arguments (exclude ./philo) \n");
        return (1);
    }
    obs = get_obs(argc, argv);
    /*make (no_of_philo) philos*/
    philos = malloc(sizeof(t_philo_param) * obs.no_of_philo);
    for (int i = 0; i < obs.no_of_philo; i++) {
        philo_init(&philos[i] ,obs ,i);
        /*if the philo can't init fork, free all philos and exit*/
        if (philos[i].fork_stat != 0) {
            while (i > 0)
                free(philos[i--]);
            return (1);
        }
    }
    /*make (no_of_philo) philosorpher*/
    th = malloc(sizeof(pthread_t) * obs.no_of_philo);
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_create(&th[i], NULL, &philo, (void *)philos) != 0) {
            printf("Failed to create thread philo[%d] \n", i + 1);
        }
    }
    /*join (no_of_philo) philosorpher*/
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread philo[%d] \n", i + 1);
        }
    }
    if (obs.died == 1)
    /*destroy all mutex to clean the program*/
        philo_destroy(philos);
    return (0);
}