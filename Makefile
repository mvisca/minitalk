# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/08/14 12:38:25 by mvisca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-------------------#
#	FORMAT			#
#-------------------#

RED			:=	\033[0;31m
GREEN		:=	\033[0;32m
YELLOW		:=	\033[0;33m
BLUE		:=	\033[0;34m
NC			:=	\033[0m

#-------------------#
#	TARGET			#
#-------------------#

NAME		:=	server
CNAME		:=	client

#-------------------#
#	INGREDIENTS		#
#-------------------#

BUILD		:=	.build/
INC			:=	include

LIBFT_DIR	:=	libft
LIBFT_INC	:=	$(LIBFT_DIR)/$(INC)
LIBFT_HD	:=	$(LIBFT_INC)/libft.h
LIBFT		:=	$(LIBFT_DIR)/libft.a

SRC_DIR		:=	src

SRC_SER		:=	server.c 
SRC_CLI		:=	client.c
SRC			:=	$(SRC_SER)
SRC			+=	$(SRC_CLI)

MT_HD		:=	$(INC)/minitalk.h

OBJ_SER		:=	$(SRC_SER:.c=.o)
OBJ_SER		:=	$(addprefix $(BUILD), $(OBJ_SER))
OBJ_CLI		:=	$(SRC_CLI:.c=.o)
OBJ_CLI		:=	$(addprefix $(BUILD), $(OBJ_CLI))
OBJ			:=	$(OBJ_SER)
OBJ			+=	$(OBJ_CLI)

DEP			:=	$(addprefix $(INC), $(notdir $(SRC:%.c=%.d)))

#-------------------#
#	FLAGS			#
#-------------------#

CC 			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS	:=	-L./$(LIBFT_DIR) -lft -I./$(LIBFT_INC) -I./$(INC)
DEBUG		:=	-g -fsanitize=address
DIR_DUP		:=	mkdir -p .build
MAKEFLAGS	+=	--no-print-directory
RM			:=	rm -r -f

#-------------------#
#	RECIPES			#
#-------------------#

all: $(LIBFT) $(NAME) | $(CNAME)

$(NAME): $(OBJ_SER) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	@echo "$(GREEN)Packing... $(NC) $(notdir $@)"
-include $(DEPS)

$(CNAME): $(OBJ_CLI) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 
	@echo "$(GREEN)Packing... $(NC) $(notdir $@)"
-include $(DEPS)

$(BUILD)%.o: $(SRC_DIR)/%.c calldeps
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -I./$(LIBFT_INC) -c $< -o $@
	@echo "$(GREEN)Creating... $(NC) $(notdir $@)"
-include $(DEP)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

callforlib:	
	@$(MAKE) -C $(LIBFT_DIR)

calldeps: $(LIBFT) $(MT_HD) $(LIBFT_HD) Makefile $(LIBFT_DIR)/Makefile 

clean:
	@$(RM) $(BUILD)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(BUILD)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: clean fclean re all
