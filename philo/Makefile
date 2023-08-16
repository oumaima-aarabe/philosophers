# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 05:39:38 by ouaarabe          #+#    #+#              #
#    Updated: 2023/08/16 05:39:39 by ouaarabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC	=	main.c\
		manage_print.c\
		philo_init.c\
		utils.c\
		routine.c\
		overseer.c
	
OBJ	=	${SRC:.c=.o}

INC		=	philo.h

CC			=	cc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=thread
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