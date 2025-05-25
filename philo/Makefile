# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 15:05:44 by yaait-am          #+#    #+#              #
#    Updated: 2025/05/25 10:04:07 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=thread
NAME = philo
SRC = philo.c init_start_program.c malloc.c helper_function.c ft_lstadd_back.c ft_lstclear.c \
		ft_lstnew.c ft_strlen.c time_function.c philo_routine.c monitoring_routine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
