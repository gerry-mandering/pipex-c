/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:18:05 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 14:03:31 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_close(int fildes)
{
	int	ret;

	ret = close(fildes);
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
