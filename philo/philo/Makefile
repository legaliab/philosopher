# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 18:14:44 by alabdull          #+#    #+#              #
#    Updated: 2023/10/09 18:14:44 by alabdull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c utils1.c utils2.c is_eating.c parsing.c run_simulation.c simulation_finished.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -pthread #-fsanitize=thread

$(NAME): $(OBJ)
		cc $(OBJ)  $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re