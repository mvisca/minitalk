# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/08/07 01:35:07 by mvisca           ###   ########.fr        #
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

NAME1		:=	client

#-------------------#
#	INGREDIENTS		#
#-------------------#

INC			:=	include/

LIBFT_DIR	:=	libft/
LIBFT_INC	:=	$(LIBFT_DIR)$(INC)
LIBFT		:=	$(LIBFT_DIR)libft.a

SRC_DIR		:=	src/

BUILD		:=	.build/

SRC1		:=	server.c server_utils.c
SRC2		:=	client.c

DEP			:=	$(SRC1)
DEP			+=	$(SRC2)

OBJ1		:=	$(addprefix $(BUILD), $(SRC1:%.c=%.o))
OBJ2		:=	$(addprefix $(BUILD), $(SRC2:%.c=%.o))

SRC1			:=	$(addprefix $(SRC_DIR), $(SRC1))
SRC2			:=	$(addprefix $(SRC_DIR), $(SRC2))
SRC				:=	$(SRC1)
SRC				+=	$(SRC2)

OBJ			:=	$(OBJ1)
OBJ			+=	$(OBJ2)

DEP			:=	$(DEP:%.c=%.d)
DEP			:=	$(addprefix $(BUILD), $(DEP))

#-------------------#
#	FLAGS			#
#-------------------#

CC 			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP

CPPFLAGS	:=	-L./$(LIBFT_DIR) -lft -I./$(LIBFT_INC) -I./$(INC)

DEBUG		:=	-g -fsanitize=address

DIR			:=	mkdir -p $(@D)

MAKEFLAGS	+=	--no-print-directory

RM			:=	rm -r -f

#-------------------#
#	RECIPES			#
#-------------------#

all: $(NAME) | callforlib

$(NAME): $(OBJ1)
	$(CC) $(CPPFLAGS) -o $@ $<

$(NAME1): $(OBJ2)
	$(CC) $(CPPFLAGS) -o $@ $<
	
$(BUILD)%.o:$(SRC)%.c $(INC) Makefile
	$(DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@
-include $(DEP)

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(RM) $(BUILD)
	$(MAKE) clean -C libft

fclean: clean
	$(RM) $(BUILD)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: clean fclean re all
