SRC = main.c \
	utils.c \
	table.c \
	diner.c \
	write.c \
	clock.c \
	status.c \
	free.c

OBJ = $(SRC:%.c=%.o)

CC = gcc -g

FLG = -Wall -Wextra -Werror

RM = rm -rf

NAME = philo

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(FLG) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: clean fclean re
