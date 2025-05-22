# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 15:05:44 by yaait-am          #+#    #+#              #
#    Updated: 2025/05/22 15:58:40 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
NAME = philo_bonus
SRC = philo_bonus.c init_data_bonus.c malloc_bonus.c helper_function_bonus.c Libft_used/ft_lstadd_back_bonus.c Libft_used/ft_lstclear_bonus.c \
		Libft_used/ft_lstnew_bonus.c Libft_used/ft_split_bonus.c Libft_used/ft_strlen_bonus.c inti_start_simulation_bonus.c \
		parent_wait_andwork_bonus.c monitoring_rotine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
