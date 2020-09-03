NAME = romans

CC = gcc

FLAGS = -Wall -Wextra -Werror

SOURCE = main.c

all: $(NAME)

$(NAME):
	@$(CC) -o $(NAME) $(FLAGS) $(SOURCE)
	@echo "$(NAME) created!"

clean:
	@rm -f $(NAME)
	@echo "$(NAME) destroyed!"

re: clean all

.PHONY: all clean re
