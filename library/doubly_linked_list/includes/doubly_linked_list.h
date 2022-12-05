/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:38:14 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 09:57:16 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

# include "../../libft/includes/libft.h"

typedef struct s_node
{
	int				pid;
	char			*cmd;
	char			**cmd_vector;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	int		size;
	t_node	*head;
	t_node	*tail;
}	t_list;

// list_basic.c
int		is_empty(t_list *list);
void	init_list(t_list *list);

// list_push_pop.c
t_node	*new_node(int pid, char *cmd, char **cmd_vector);
void	push_head_side(t_list *list, t_node *new_node);
void	push_tail_side(t_list *list, t_node *new_node);
t_node	*pop_head_side(t_list *list);
t_node	*pop_tail_side(t_list *list);

// list_clear.c
void	clear_list(t_list *list);

#endif
