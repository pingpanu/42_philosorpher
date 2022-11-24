/*input.c is the sub_void of main to check input.
1) no_of_philo can't be zero, if not exit
2) die_time, eat_time, sleep_time can't be less than 60
3) non_numeric function is NOT ACCEPTED
4) I also check if number exceed int limits*/

#include "philo.h"

static t_input  get_input(int argc, char **argv)
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

static int  str_isnumeric(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

int     valid_arguments(int argc, char **argv, t_env *prog)
{
    if (argc < 5 || argc > 6) {
        printf("You must type 4 or 5 arguments (exclude ./philo) \n");
        return (0);
    }
    for (int i = 1; i < argc; i++) {
        if (!str_isnumeric(argv[i])) {
            printf("argv[%d] contain nonumeric character\n", i);
            return (0);
        }
    }
    prog->inputs = get_input(argc, argv);
    if (prog->inputs.no_of_philo == 0 || prog->inputs.no_of_philo > 200) {
        printf("Your number of philosopher should be between 1 to 200 \n");
        return (0);
    }
    else if (prog->inputs.die_time < 60) {
        printf("Your die time should be at least 60\n");
        return (0);
    }
    else if (prog->inputs.eat_time < 60) {
        printf("Your eat time should be at least 60\n");
        return (0);
    }
    else if (prog->inputs.sleep_time < 60) {
        printf("Your sleep time should be at least 60\n");
        return (0);
    }
    prog->death_flag = 0;
    //prog->eat_end = 0;
    prog->philos = malloc(sizeof(t_philo_param) * prog->inputs.no_of_philo);
    /*exit when fail to malloc*/
    if (prog->philos == NULL) {
        free(prog->philos);
        printf("Failed to malloc philos\n");
        return (0);
    }
    return (1);
}