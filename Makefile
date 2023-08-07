# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/07/10 18:32:00 by mvisca-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= client server

LIBFT		:= libft/libft.a

all: $(NAME)

server: server.c $(LIBFT)
	cc -g -fsanitize=address -L./libft -lft -I. -I./libft/include server.c -o server

client: client.c $(LIBFT)
	cc -g -fsanitize=address -L./libft -lft -I. -I./libft/include client.c -o client

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf server client
	$(MAKE) clean -C libft

fclean: clean
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: clean fclean re all


NAME minitalk

NAME1 server

NAME2 client

LIBFT_DIR libft/
LIBFT_INC libft/include
INC include
SRC_DIR src

SRC1 server.c server_utils.c
SRC2 client.c
SRC $(addprefix $(SRC_DIR), $(SRC))
OBJ $(SRC:%.c=%.o)
DEP 

CC cc

CPFLAGS -Wall -Wextra -Werror

CPPFLAGS -L./libf -lft -I./libft/include -./include


