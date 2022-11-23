#include "philo.h"

/*This fuction is use to receive current time of the machine*/

long long   get_ms(void)
{
    struct timeval  cur_time;
    long long       ret;

    gettimeofday(&cur_time, NULL);
    ret = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
    return (ret);
}

long long   diff_ms(long long time)
{
    return (get_ms() - time);
}
/*
int main(void)
{
    long long start;

    start = get_ms();
    sleep(5);
    printf("time diff in ms = %lld\n", diff_ms(start));
    return (0);
}*/