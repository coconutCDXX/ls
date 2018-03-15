NAME	= ls
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -c
FILES	= ./srcs/main.c ./srcs/sort.c ./srcs/printing.c ./srcs/setparams.c
OBJ		= main.o sort.o printing.o setparams.o
LIB		= -I.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)
$(OBJ):
	$(CC) $(CFLAGS) $(FILES) $(LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
