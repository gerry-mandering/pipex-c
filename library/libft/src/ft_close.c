/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:18:05 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/13 21:20:16 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_close(int fildes)
{
	int	flag;

	flag = close(fildes);
	if (flag == -1)
		ft_exit("file close failure", STDERR_FILENO, EXIT_FAILURE);
	return (flag);
}
