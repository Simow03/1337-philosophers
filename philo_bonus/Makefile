NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES = main.c process_setup.c routine.c ../utils/error_handle.c ../utils/ft_atol.c \
			../utils/ft_iswhitespace.c ../utils/ft_strcmp.c ../utils/time.c ../utils/ft_isdigit.c\

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