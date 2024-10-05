CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = my_ls.c
OBJ = $(SRC:.c=.o)
EXEC = my_ls

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
