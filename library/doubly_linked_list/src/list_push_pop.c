/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:46:14 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 09:55:00 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doubly_linked_list.h"

t_node	*new_node(int pid, char *cmd, char **cmd_vector)
{
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	new_node->pid = pid;
	new_node->cmd = cmd;
	new_node->cmd_vector = cmd_vector;
	return (new_node);
}

//Before:  | list->head | first_node |
//After:   | list->head | new_node | first_node |
void	push_head_side(t_list *list, t_node *new_node)
{
	t_node	*first_node;

	first_node = list->head->next;
	list->head->next = new_node;
	new_node->prev = list->head;
	new_node->next = first_node;
	first_node->prev = new_node;
	(list->size)++;
}

//Before:  | last_node | list->tail |
//After:   | last_node | new_node | list->tail |
void	push_tail_side(t_list *list, t_node *new_node)
{
	t_node	*last_node;

	last_node = list->tail->prev;
	list->tail->prev = new_node;
	new_node->next = list->tail;
	new_node->prev = last_node;
	last_node->next = new_node;
	(list->size)++;
}

//Before:  | list->head | first_node | first_node->next |
//After:   | list->head | first_node->next |
t_node	*pop_head_side(t_list *list)
{
	t_node	*first_node;

	if (is_empty(list))
		ft_exit("list is empty", EXIT_FAILURE);
	first_node = list->head->next;
	list->head->next = first_node->next;
	first_node->next->prev = list->head;
	first_node->prev = NULL;
	first_node->next = NULL;
	(list->size)--;
	return (first_node);
}

//Before:  | last_node->prev | last_node | list->tail |
//After:   | last_node->prev | list->tail |
t_node	*pop_tail_side(t_list *list)
{
	t_node	*last_node;

	if (is_empty(list))
		ft_exit("list is Empty", EXIT_FAILURE);
	last_node = list->tail->prev;
	list->tail->prev = last_node->prev;
	last_node->prev->next = list->tail;
	last_node->prev = NULL;
	last_node->next = NULL;
	(list->size)--;
	return (last_node);
}
