/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:34:32 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/03 15:01:30 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t data_type_size)
{
	void	*ptr;

	ptr = malloc(count * data_type_size);
	if (ptr == NULL)
		ft_exit("Error: malloc assertion failure", EXIT_FAILURE);
	ft_bzero(ptr, (count * data_type_size));
	return (ptr);
}
