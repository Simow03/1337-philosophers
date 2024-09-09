NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES = main.c routine.c thread_setup.c error_handle.c time.c utils.c

OBJECTS = $(SOURCES:.c=.o)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean :
	rm -f $(OBJECTS) $(OBJECTS)

fclean : clean
	rm -f $(NAME) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re