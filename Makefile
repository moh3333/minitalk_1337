# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 17:58:48 by mthamir           #+#    #+#              #
#    Updated: 2024/03/13 17:16:36 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

FLAGS = -Wall -Wextra -Werror

CC = cc

SRC_S = server.c

SRC_C = client.c

OBJ_S = server.o

OBJ_C = client.o

SRC_BONUS_S = server_bonus.c 

SRC_BONUS_C = client_bonus.c 

OBJ_BONUS_S = server_bonus.o

OBJ_BONUS_C = client_bonus.o

all : $(NAME) client

$(NAME) : $(OBJ_S) minitalk.h
	$(CC) $(FLAGS) $< -o $@

client : $(OBJ_C) minitalk.h
	$(CC) $(FLAGS) $< -o $@

bonus : client_b server_b

client_b : $(OBJ_BONUS_C) minitalk_bonus.h
	$(CC) $(FLAGS) $< -o $@

server_b : $(OBJ_BONUS_S) minitalk_bonus.h
	$(CC) $(FLAGS) $< -o $@

%.o : %.c 
	$(CC) $(FLAGS) $< -c -o $@

clean : 
	rm -f $(OBJ_S) $(OBJ_C)
	rm -f $(OBJ_BONUS_S) $(OBJ_BONUS_C)

fclean : clean
	rm -f $(NAME) client
	rm -f server_b client_b

re : fclean all

