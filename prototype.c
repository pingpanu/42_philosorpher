#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*in assignment, global variable IS NOT ALLOWED*/
pthread_t   philosorpher[5];
pthread_mutex_t forks[5];

void*    function(int *i)
{
    int     n;

    n = *i;
    printf("Philosorpher %d is thinking\n", n);
    /*philosorpher must take two forks before eating*/
    pthread_mutex_lock(&forks[n]);
    pthread_mutex_lock(&forks[(n + 1) % 5]);
    printf("Philosorpher %d is eating\n", n);
    usleep(3);
    pthread_mutex_unlock(&forks[n]);
    pthread_mutex_unlock(&forks[(n + 1) % 5]);
    printf("Philosorpher %d is finished eating\n", n);
    return (NULL);
}

int main()
{
    int i;

    for (i = 0; i < 5; i++)
        pthread_mutex_init(&forks[i], NULL);
    for (i = 0; i < 5; i++)
        pthread_create(&philosorpher[i], NULL, (void *)&function, (void *)&i);
    for (i = 0; i < 5; i++)
        pthread_join(philosorpher[i], NULL);
    for (i = 0; i < 5; i++)
        pthread_mutex_destroy(&forks[i]);
    return (0);
}