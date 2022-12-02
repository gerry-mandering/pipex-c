/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:50:51 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/02 18:10:45 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_exit(const char *msg, int status)
{
	if (msg == NULL)
		perror("bash");
	else
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	exit (status);
}
