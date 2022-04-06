# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 20:16:19 by omoudni           #+#    #+#              #
#    Updated: 2022/04/07 00:02:29 by omoudni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define compiling
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $1 -c $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Creating executable $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $1
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define cleaning 
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Cleaning $1 $(shell tput sgr0)"
	@rm -rf $1 > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define fcleaning 
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Fcleaning $1 $(shell tput sgr0)"
	@rm -f $1 > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

SRC_DIR = src/
OBJ_DIR = bin/
INC_DIR = includes/

SRCS = pipex.c \
	   split.c \
	   utils_1.c \
	   utils_2.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c\
	   utils_3.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))

PIPEX = pipex

CC = gcc

#CFLAGS = -Werror -Wextra -Wall -g -fsanitize=address
CFLAGS = -g -fsanitize=address

CPPFLAGS = -I$(INC_DIR)

all: $(PIPEX)

$(PIPEX): $(OBJS)
	$(call finishing, $(PIPEX))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(call compiling, $@, $<)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/gnl/

clean:
	$(call cleaning, $(OBJ_DIR))

fclean: clean
	$(call fcleaning, $(PIPEX))

bonus: all

re: fclean all

.PHONY: all clean fclean re
