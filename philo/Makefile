CC = cc
CFLAGS = -Werror -Wall -Wextra -g -I. -MMD -pthread

MAIN = main.c input_parsing.c initialization_of_threads.c data_init.c philo.c cleanup.c 

CFILES = $(MAIN)
OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)

NAME = philo

HEADER = philosophers.h

CREATE = ar rcs
REMOVE = rm -f


%.o: %.c  $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

fclean: clean
	$(REMOVE) $(NAME)

clean:
	$(REMOVE) $(OFILES)
	$(REMOVE) $(DFILES)

re: fclean all

.PHONY: all clean fclean re