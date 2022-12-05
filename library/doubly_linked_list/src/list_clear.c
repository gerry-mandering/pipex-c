/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:45:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 09:54:01 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doubly_linked_list.h"

void	clear_list(t_list *list)
{
	t_node	*current_node;
	t_node	*next_node;

	current_node = list->head->next;
	while (current_node->next != NULL)
	{
		next_node = current_node->next;
		//vector free ㅊㅜ가
		ft_free(current_node);
		current_node = next_node;
	}
	ft_free(list->head);
	ft_free(list->tail);
}
