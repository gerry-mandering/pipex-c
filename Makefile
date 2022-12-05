# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:54:09 by minseok2          #+#    #+#              #
#    Updated: 2022/12/05 14:20:26 by minseok2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -rf

LIBFT_DIR = library/libft
LIBFT_NAME = ft
LIBDLL_DIR = library/doubly_linked_list
LIBDLL_NAME = dll

# mandatory
HEADER_DIR = includes

SRCS_DIR = src/mandatory
SRCS = pipex.c \
	   parse.c \
	   execute.c \
	   utils.c

OBJS_DIR = objs/mandatory
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# bonus
BONUS_HEADER_DIR = includes

BONUS_SRCS_DIR = src/bonus
BONUS_SRCS = pipex_bonus.c \
			 parse_bonus.c \
			 execute_bonus.c \
			 utils_bonus.c

BONUS_OBJS_DIR = objs/bonus
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJS_DIR)/%.o)

TOTAL_OBJS_DIR = objs

all: $(NAME)

bonus:
	make BONUS=1 all

clean:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBDLL_DIR)
	$(RM) $(RMFLAGS) $(TOTAL_OBJS_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	make fclean
	make all

ifndef BONUS
$(NAME): $(OBJS)
	make all -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -o $@ $^
else
$(NAME): $(BONUS_OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBDLL_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBDLL_DIR) -l$(LIBDLL_NAME) -o $@ $^
endif

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR)

$(BONUS_OBJS): $(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(BONUS_HEADER_DIR)

.PHONY : all bonus clean fclean re
