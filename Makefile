# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:54:09 by minseok2          #+#    #+#              #
#    Updated: 2022/12/03 14:58:32 by minseok2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -rf

LIBFT_DIR = library/libft
LIBFT_NAME = ft
LIBPRINTF_DIR = library/ft_printf
LIBPRINTF_NAME = printf

# mandatory
HEADER_DIR = includes

SRCS_DIR = src
SRCS = pipex.c \
	   parse/parse.c

OBJS_DIR = objs/mandatory
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# bonus
BONUS_HEADER_DIR = bonus/includes

BONUS_SRCS_DIR = bonus/src
BONUS_SRCS = checker_bonus.c \

BONUS_OBJS_DIR = objs/bonus
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJS_DIR)/%.o)

TOTAL_OBJS_DIR = objs

all: $(NAME)

bonus: $(NAME) $(BONUS_NAME)

clean:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBPRINTF_DIR)
	$(RM) $(RMFLAGS) $(TOTAL_OBJS_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(BONUS_NAME)

re:
	make fclean
	make all

$(NAME): $(OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBPRINTF_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBPRINTF_DIR) -l$(LIBPRINTF_NAME) -o $@ $^

$(BONUS_NAME): $(BONUS_OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBPRINTF_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBPRINTF_DIR) -l$(LIBPRINTF_NAME) -o $@ $^

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)/{parse,}
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR)

$(BONUS_OBJS): $(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)/{parse_bonus}
	$(CC) $(CFLAGS) -c $< -o $@ -I$(BONUS_HEADER_DIR)

.PHONY : all bonus clean fclean re
