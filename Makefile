# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/08/16 15:33:39 by mvisca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_SRC	:=	src/server.c
CLIENT_SRC	:=	src/client.c
SRC			:=	SERVER_SRC CLIENT_SRC

HEADERS		:=	include/minitalk.h

CC			:=	cc -Wall -Wextra -Werror -MMD
CC_FLAGS	:=	-Llibft -lft

SERVER_OBJS	:=	$(addprefix .build/, $(notdir $(SERVER_SRC:.c=.o)))
CLIENT_OBJS	:=	$(addprefix .build/, $(notdir $(CLIENT_SRC:.c=.o)))
OBJS		:=	$(SERVER_OBJS) $(CLIENT_OBJS)

SERVER_DEPS	:=	$(addprefix .build/, $(notdir $(SERVER_SRC:.c=.d)))
CLIENT_DEPS	:=	$(addprefix .build/, $(notdir $(CLIENT_SRC:.c=.d)))
DEPS		:=	$(SERVER_DEPS) $(CLIENT_DEPS)


all: libft server client

libft:
	@make -C libft --silent

server: $(SERVER_OBJS) $(HEADERS)
	$(CC) $(SERVER_OBJS) $(CC_FLAGS) -o server

client: $(CLIENT_OBJS) $(HEADERS)	
	$(CC) $(CLIENT_SRC) $(CC_FLAGS) -o client

.build/%.o: src/%.c $(HEADERS) libft/libft.a Makefile
	@mkdir -p .build
	$(CC) $< -c -o $@
-include $(DEPS)

clean:
	@rm -rdf .build
	@$(MAKE) clean -C libft --silent

fclean: clean
	@$(MAKE) fclean -C libft --silent
	@rm -rf .build server client

re: fclean all

test:
	@echo "$(DEPS)"

.PHONY:	all libft clean fclean
