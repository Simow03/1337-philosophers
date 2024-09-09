NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES = main.c process_setup.c routine.c error_handle.c time.c utils.c\

OBJECTS = $(SOURCES:.c=.o)

%.o : %.c philo_bonus.h
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