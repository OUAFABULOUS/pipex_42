# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 20:16:19 by omoudni           #+#    #+#              #
#    Updated: 2022/03/31 21:46:42 by omoudni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define compiling
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $1 -c $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing_m
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Creating executable $1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS_M) $(OBJS_M) -o $1
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

SRC_DIR_M = SRC_M/
OBJ_DIR_M = bin_m/
INC_DIR_M = includes_m/

SRCS_M = pipex.c \
		 split.c \
		 utils_1.c \
		 utils_2.c \
		 utils_3.c

OBJS_M = $(addprefix $(OBJ_DIR_M), $(SRCS_M:%.c=%.o))

PIPEX = pipex

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address
endif

CPPFLAGS_M = -I$(INC_DIR_M)

all: $(PIPEX)

$(PIPEX): $(OBJS_M)
	$(call finishing_m, $(PIPEX))

$(OBJ_DIR_M)%.o: $(SRC_DIR_M)%.c | $(OBJ_DIR_M)
	$(call compiling, $@, $<)

$(OBJ_DIR_M):
	@mkdir -p $(OBJ_DIR_M)

clean:
	$(call cleaning, $(OBJ_DIR_M))

fclean: clean
	$(call fcleaning, $(PIPEX))

bonus: all

re: fclean all

.PHONY: all clean fclean re
