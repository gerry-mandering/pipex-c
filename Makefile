# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 14:54:09 by minseok2          #+#    #+#              #
#    Updated: 2022/12/10 16:58:54 by minseok2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -rf

LIBFT_DIR = library/libft
LIBFT_NAME = ft
LIBGNL_DIR = library/get_next_line
LIBGNL_NAME = gnl

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
			 utils_bonus.c \
			 logic/parse_bonus.c \
			 logic/parse_utils_bonus.c \
			 logic/get_heredoc_input.c \
			 logic/allocate_fd_bonus.c \
			 logic/allocate_pid_arr_bonus.c \
			 logic/set_pipe_bonus.c \
			 logic/do_fork_bonus.c \
			 logic/parent_waiting_bonus.c \
			 logic/child_execute_bonus.c

BONUS_OBJS_DIR = objs/bonus
BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJS_DIR)/%.o)

TOTAL_OBJS_DIR = objs

all: $(NAME)

bonus:
	make BONUS=1 all

clean:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBGNL_DIR)
	$(RM) $(RMFLAGS) $(TOTAL_OBJS_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	make fclean
	make all

ifndef BONUS
$(NAME): $(OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBGNL_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBGNL_DIR) -l$(LIBGNL_NAME) -o $@ $^
else
$(NAME): $(BONUS_OBJS)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBGNL_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBGNL_DIR) -l$(LIBGNL_NAME) -o $@ $^
endif

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR)

$(BONUS_OBJS): $(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)/{logic,}
	$(CC) $(CFLAGS) -c $< -o $@ -I$(BONUS_HEADER_DIR)

.PHONY : all bonus clean fclean re
