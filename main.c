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
    pthread_t  *th;
    pthread_mutex_t *forks;

    if (argc < 5 || argc > 6) {
        printf("You must type 4 or 5 arguments (exclude ./philo) \n");
        return (1);
    }
    obs = get_obs(argc, argv);
    /*make (no_of_philo) forks*/
    forks = malloc(sizeof(pthread_mutex_t) * obs.no_of_philo);
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_mutex_init(&forks[i], NULL) != 0) {
            printf("Failed to initialize fork[%d]\n", i);
        }
    }
    /*make (no_of_philo) philosorpher*/
    th = malloc(sizeof(pthread_t) * obs.no_of_philo);
    for (int i = 0; i < obs.no_of_philo; i++)
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_create(&th[i], NULL, &philo, NULL) != 0) {
            printf("Failed to create thread philo[%d] \n", i + 1);
        }
    }
    /*join (no_of_philo) philosorpher*/
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread philo[%d] \n", i + 1);
        }
    }
    /*destroy all mutex to clean the program*/
    for (int i = 0; i < obs.no_of_philo; i++) {
        if (pthread_mutex_destroy(&forks) != 0) {
            printf("Fork[%d] destroyed\n", i);
        }
    }
    return (0);
}