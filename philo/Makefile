NAME = philo

SRC	=	main.c\
		manage_print.c\
		philo_init.c\
		utils.c
	
OBJ	=	${SRC:.c=.o}

INC		=	philo.h

CC			=	cc
CFLAGS		= -fsanitize=address
RM			=	rm -rf

all: $(UTILS) $(NAME)

$(NAME): $(OBJ) $(INC)
	@ $(CC) $(CFLAGS) -o $@  $(OBJ)

%.o: %.c $(INC)
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re