/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:50:59 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 09:52:24 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

int	wexitstatus(int status)
{
	int	exit_status;

	exit_status = ((unsigned)status >> 8) & 0xff;
	return (exit_status);
}
