# VARIABLE DECLARATION ############################################################################

NAME =			philo

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra -O3 -pthread
# CFLAGS =		-fsanitize=thread -D TSAN_OPTIONS=second_deadlock_stack=1

HEADERS =		./includes

BLACK	= 		\033[0;30m
RED		= 		\033[0;91m
GREEN	= 		\033[0;92m
YELLOW	= 		\033[0;93m
BLUE	= 		\033[0;94m
PURPLE	= 		\033[0;35m
CYAN	= 		\033[0;96m
WHITE	= 		\033[0;37m

SRCS =			./srcs/ft_atoi.c \
				./srcs/struct_init.c \
				./srcs/main.c \
				./srcs/parsing.c \
				./srcs/philo_actions.c \
				./srcs/time_management.c \
				./srcs/mutex_management.c \
				./srcs/free.c \
				./srcs/simulation.c \

OBJS =			$(SRCS:.c=.o)

# RULES ###########################################################################################

all: $(NAME)
$(NAME): $(OBJS)
	echo "$(CYAN)Compiling Philosophers :$(WHITE)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo "$(GREEN)Philosophers successfully compiled ! \n\n$(WHITE)"

./srcs/%.o: ./srcs/%.c $(HEADERS)/philo.h
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

clean:
	echo "$(YELLOW)Deleting all files exept binaries$(WHITE)"
	rm -rf $(OBJS)

fclean: clean
	echo "$(PURPLE)Deleting binaries$(WHITE)"
	rm -rf $(NAME)

re:
	make -s fclean
	make -s all

.SILENT:

.PHONY: all clean fclean re
