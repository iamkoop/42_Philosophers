CC = cc
CFLAGS = -Werror -Wall -Wextra -g -I. -I42_Libft -MMD

MAIN = main.c input_parsing.c

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