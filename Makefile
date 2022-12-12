# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 14:22:49 by minseok2          #+#    #+#              #
#    Updated: 2022/12/12 20:57:51 by minseok2         ###   ########.fr        #
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

SRCS_DIR = srcs/mandatory
SRCS = pipex.c \
	   utils.c \
	   logic/init/init.c \
	   logic/init/init_utils.c \
	   logic/init/parse_filename.c \
	   logic/init/set_heredoc_info/execute_mktemp.c \
	   logic/init/set_heredoc_info/make_random_name.c \
	   logic/init/set_heredoc_info/set_heredoc_info.c \
	   logic/init/get_heredoc_input.c \
	   logic/init/count_total_cmd.c \
	   logic/init/allocate_pipe_arr.c \
	   logic/init/set_cmd_arr.c \
	   logic/set_pipe.c \
	   logic/do_fork.c \
	   logic/parent_waiting.c \
	   logic/child_execute.c

OBJS_DIR = objs/mandatory
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# bonus
BONUS_HEADER_DIR = includes

BONUS_SRCS_DIR = srcs/bonus
BONUS_SRCS = pipex_bonus.c \
			 utils_bonus.c \
			 logic/init/init_bonus.c \
			 logic/init/init_utils_bonus.c \
			 logic/init/parse_filename_bonus.c \
			 logic/init/set_heredoc_info/execute_mktemp_bonus.c \
			 logic/init/set_heredoc_info/make_random_name_bonus.c \
			 logic/init/set_heredoc_info/set_heredoc_info_bonus.c \
			 logic/init/get_heredoc_input_bonus.c \
			 logic/init/count_total_cmd_bonus.c \
			 logic/init/allocate_pipe_arr_bonus.c \
			 logic/init/set_cmd_arr_bonus.c \
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
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBGNL_DIR)
	$(RM) $(RMFLAGS) $@ $(BONUS_OBJS_DIR)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBGNL_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBGNL_DIR) -l$(LIBGNL_NAME) -o $@ $^
else
$(NAME): $(BONUS_OBJS)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBGNL_DIR)
	$(RM) $(RMFLAGS) $@ $(OBJS_DIR)
	make all -C $(LIBFT_DIR)
	make all -C $(LIBGNL_DIR)
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(LIBGNL_DIR) -l$(LIBGNL_NAME) -o $@ $^
endif

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)/{logic/init/set_heredoc_info,}
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR)

$(BONUS_OBJS): $(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)/{logic/init/set_heredoc_info,}
	$(CC) $(CFLAGS) -c $< -o $@ -I$(BONUS_HEADER_DIR)

.PHONY : all bonus clean fclean re
