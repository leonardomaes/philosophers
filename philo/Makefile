#Compile Options
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

#
SRC =	main.c utils.c philo_utils.c routine.c
#

# Commands
RM = rm -rf
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $*.c -o $*.o

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
clean:
			$(RM) $(OBJ)
fclean: clean
			$(RM) $(NAME)
re: fclean all



