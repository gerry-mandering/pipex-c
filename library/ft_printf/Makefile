# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 14:17:19 by minseok2          #+#    #+#              #
#    Updated: 2022/11/10 20:23:49 by minseok2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rcs
RM = rm
RMFLAGS = -rf

HEADER_DIR = includes

SRCS_DIR = src
SRCS = branch_c.c \
		branch_di.c \
		branch_di_util1.c \
		branch_di_util2.c \
		branch_di_util3.c \
		branch_p.c \
		branch_p_util1.c \
		branch_s.c \
		branch_type.c \
		branch_u.c \
		branch_u_util1.c \
		branch_u_util2.c \
		branch_x.c \
		branch_x_util1.c \
		branch_x_util2.c \
		branch_x_util3.c \
		ft_printf.c \
		judgement_functions.c \
		libft_functions.c \
		parse_funcions.c \
		string_util_functions.c

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJS_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re:
	make fclean
	make all

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR)

.PHONY : all bonus clean fclean re
