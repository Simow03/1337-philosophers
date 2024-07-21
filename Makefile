NAME = philo

CC = cc

CFLAGS = -fsanitize=address -Wall -Wextra -Werror -pthread

SOURCES = main.c routine.c utils/error_handle.c utils/ft_atol.c \
			utils/ft_isdigit.c utils/ft_iswhitespace.c utils/ft_strcmp.c \
			utils/time.c routine_utils.c

OBJECTS = $(SOURCES:.c=.o)

%.o : %.c philosophers.h
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