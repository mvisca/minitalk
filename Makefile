# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/08/19 20:01:12 by mvisca-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------------#
#	FORMAT								#
#---------------------------------------#

RED 		:= \033[0;31m
GREEN 		:= \033[0;32m
YELLOW 		:= \033[0;33m
BLUE 		:= \033[0;34m
NC 			:= \033[0m

#---------------------------------------#
#	FILES								#
#---------------------------------------#

SERVER_SRC	:=	src/server.c
CLIENT_SRC	:=	src/client.c

#---------------------------------------#
#	INGREDIENTS							#
#---------------------------------------#

HEADERS		:=	include/minitalk.h

CC			:=	cc -Wall -Wextra -Werror
DEBUG		:=	-g -fsanitize=address
CC_FLAGS	:=	-Llibft -lft

SERVER_OBJS	:=	$(addprefix .build/, $(notdir $(SERVER_SRC:.c=.o)))
CLIENT_OBJS	:=	$(addprefix .build/, $(notdir $(CLIENT_SRC:.c=.o)))

DEPS		:=	$(SERVER_OBJS:.o=.d) $(CLIENT_OBJS:.o=.d)

#---------------------------------------#
#	RECIPES								#
#---------------------------------------#

all: libft server client | callforlib

libft:
	@make -C libft --silent

server: $(SERVER_OBJS) $(HEADERS)
	@$(CC) $(SERVER_OBJS) $(CC_FLAGS) $(DEBUG) -MMD -o server
	@echo "$(YELLOW)Packing $(RED)$(notdir $@) $(YELLOW)ready!$(NC)"

client: $(CLIENT_OBJS) $(HEADERS)	
	@$(CC) $(CLIENT_OBJS) $(CC_FLAGS) $(DEBUG) -MMD -o client
	@echo "$(YELLOW)Packing $(RED)$(notdir $@) $(YELLOW)ready!$(NC)"

.build/%.o: src/%.c $(HEADERS) libft/libft.a Makefile
	@mkdir -p .build
	@$(CC) -MMD $< -c -o $@
	@echo "$(GREEN)Building...  $(NC)$(notdir $<) $(RED)-> $(NC)$(notdir $@)"

-include $(DEPS)

#---------------------------------------#
#	OTHERS								#
#---------------------------------------#

callforlib: libft

clean:
	@rm -rdf .build
	@$(MAKE) clean -C libft --silent

fclean: clean
	@$(MAKE) fclean -C libft --silent
	@rm -rf .build server client

re: fclean all

.PHONY:	all libft clean fclean
