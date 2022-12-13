/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:39:19 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:13:30 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/pipex_bonus.h"

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

pid_t	ft_fork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	wexitstatus(int status)
{
	int	exit_status;

	exit_status = ((unsigned)status >> 8) & 0xff;
	return (exit_status);
}
