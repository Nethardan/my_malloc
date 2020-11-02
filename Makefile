SRC		:= src/malloc.c
SRC		+= src/utils.c
#SRC		+= src/free.c

TEST	= src/main.c

OBJ		= $(SRC:.c=.o)

NAME	= libmy_malloc.so

BIN		= test

CC		= gcc

CFLAGS	+= -Wall -Wextra -I./include

all: $(NAME)

$(NAME): CFLAGS += -c -fpic
$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

$(BIN): CFLAGS += -L. -lmy_malloc -g3
$(BIN): $(NAME) $(TEST)
	$(CC) -o $(BIN) $(CFLAGS) $(TEST)

clean:
	rm -rf $(OBJ) *~ *# vgcore.*

fclean: clean
	rm -rf $(NAME) $(BIN)

re: fclean all

.PHONY: all test clean flcean re