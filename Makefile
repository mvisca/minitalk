# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 20:03:58 by mvisca-g          #+#    #+#              #
#    Updated: 2023/08/09 16:52:43 by mvisca           ###   ########.fr        #
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

SNAME		:=	server
CNAME		:=	client

#-------------------#
#	INGREDIENTS		#
#-------------------#

LIBFT_DIR	:=	libft
LIBFT_INC	:=	libft/include
LIBFT		:=	libft/libft.a

SRC_DIR		:=	src/

SRC_SER		:=	server.c 	\
				server_utils.c
SRC_CLI		:=	client.c
SRC			:=	$(SRC_SER)
SRC			+=	$(SRC_CLI)

BUILD		:=	.build/
INC			:=	include/

OBJ_SER		:=	$(SRC_SER:.c=.o)
OBJ_CLI		:=	$(SRC_CLI:.c=.o)
OBJ			:=	$(OBJ_SER)
OBJ			+=	$(OBJ_CLI)
OBJ			:=	$(addprefix $(BUILD), $(OBJ))

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

all: $(SNAME) $(CNAME) | callforlib

$(SNAME): $(addprefix $(BUILD), $(OBJ_SER)) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(CNAME): $(addprefix $(BUILD), $(OBJ_CLI)) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 

$(BUILD)%.o: $(SRC_DIR)%.c Makefile | $(LIBFT_DIR)/Makefile
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@	
	@echo "$(GREEN)Creating... $(NC) $(notdir $@)"
-include $(DEP)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

test:
	@echo "$(SRC_SER)"

clean:
	$(RM) $(BUILD)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(BUILD)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

callforlib:
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: clean fclean re all callforlib test
