/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:18:05 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/04 16:20:22 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_close(int fildes)
{
	int	flag;

	flag = close(fildes);
	if (flag == -1)
		ft_exit(NULL, EXIT_FAILURE);
	return (flag);
}
