# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 14:19:43 by sunghwki          #+#    #+#              #
#    Updated: 2024/03/26 09:05:20 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

CLINK = -lpthread

SOURCE =  ft_lib_bonus.c  ft_itoa_bonus.c ft_strjoin_bonus.c ft_print_msg_bonus.c \
			state_eating_bonus.c state_assist_bonus.c state_thinking_bonus.c state_sleeping_bonus.c \
			init_bonus.c philo_bonus.c thread_bonus.c main_bonus.c

OBJECTS = $(SOURCE:.c=.o)

NAME = philo_bonus

$(NAME) : $(OBJECTS)
			$(CC) $(CFLAGS) -o $(NAME) $(SOURCE) $(CLINK)

all : $(NAME)

bonus : $(NAME)

clean :
	rm -rf $(OBJECTS)

fclean :
	make clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re bonus
