# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 20:16:19 by omoudni           #+#    #+#              #
#    Updated: 2022/04/12 15:48:12 by omoudni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define compiling_m
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling - mandatory$1 $(shell tput sgr0)"
		@$(CC) $(CFLAGS) $(CPPFLAGS) -o $1 > /dev/null -c $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define compiling_b
	@echo -n "$(shell tput bold)$(shell tput setaf 3)Compiling - bonus$1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $1 -c $2
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing_m
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Creating executable - mandatory$1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS_M) $(OBJS_M) -o $1
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define finishing_b
	@echo -n "$(shell tput bold)$(shell tput setaf 2)Creating executable - bonus$1 $(shell tput sgr0)"
	@$(CC) $(CFLAGS) $(CPPFLAGS_B) $(OBJS_B) -o $1
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define cleaning 
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Cleaning $1 $(shell tput sgr0)"
	@rm -rf $1 $2> /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

define fcleaning 
	@echo -n "$(shell tput bold)$(shell tput setaf 8)Fcleaning $1 $(shell tput sgr0)"
	@rm -f $1 > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 2)√$(shell tput sgr0)"
endef

SRC_DIR_M = mandatory/src_m/
OBJ_DIR_M = mandatory/bin_m/
INC_DIR_M = mandatory/includes_m/

SRC_DIR_B = bonus/src_b/
OBJ_DIR_B = bonus/bin_b/
INC_DIR_B = bonus/includes_b/

SRCS_M = pipex.c \
		 split.c \
		 utils_1.c \
		 utils_2.c \
		 utils_3.c \
		 utils_4.c \
		 utils_5.c

SRCS_B = pipex.c \
		 split.c \
		 utils_1.c \
		 utils_2.c \
		 utils_3.c \
		 utils_4.c \
		 utils_5.c \
		 gnl/get_next_line.c \
		 gnl/get_next_line_utils.c

OBJS_M = $(addprefix $(OBJ_DIR_M), $(SRCS_M:%.c=%.o))
OBJS_B = $(addprefix $(OBJ_DIR_B), $(SRCS_B:%.c=%.o))

PIPEX = pipex

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g3

DEBUG =
ifdef DEBUG
CFLAGS += -fsanitize=address
endif

CPPFLAGS_M = -I$(INC_DIR_M)
CPPFLAGS_B = -I$(INC_DIR_B)

all: $(PIPEX)

$(PIPEX): $(OBJS_M)
	$(call finishing_m, $(PIPEX))

$(OBJ_DIR_M):
	@mkdir -p $(OBJ_DIR_M)

$(OBJ_DIR_M)%.o: $(SRC_DIR_M)%.c | $(OBJ_DIR_M)
	$(call compiling_m, $@, $<)


$(OBJ_DIR_B):
	@mkdir -p $(OBJ_DIR_B)
	$(eval FOLDERS = $(shell find $(SRC_DIR_B)/* -type d ))
	@mkdir -p $(FOLDERS:$(SRC_DIR_B)%=$(OBJ_DIR_B)%)

$(OBJ_DIR_B)%.o: $(SRC_DIR_B)%.c | $(OBJ_DIR_B)
	$(call compiling_b, $@, $<)

clean:
	$(call cleaning, $(OBJ_DIR_M), $(OBJ_DIR_B))

fclean: clean
	$(call fcleaning, $(PIPEX))

bonus: $(OBJS_B)
	$(call finishing_b, $(PIPEX))

re: fclean all

.PHONY: all clean fclean re
