NAME = philosopher
FLAGS = -Wall -Wextra -Werror
CC = gcc

SRCS = 	main.c \
		input.c \
		philo.c \
		microsecond.c \
		utils.c \
		prog_init.c \
#		referees.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	@ $(CC) $(FLAGS) $^ -I ./ -o $(NAME)
	@ rm $(OBJS)
	
%.o:%.c
	@ $(CC) -c $(FLAGS) $^ -I ./

clean :
	rm $(NAME)

re : clean all

.PHONY : all clean re