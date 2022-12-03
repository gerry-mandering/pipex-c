/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:18:05 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/03 15:01:42 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_close(int fildes)
{
	int	flag;

	flag = close(fildes);
	if (flag == -1)
		ft_exit("Error: file close failure", EXIT_FAILURE);
	return (flag);
}
