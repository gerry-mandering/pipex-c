/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:14:15 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:13:50 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/pipex_bonus.h"

void	set_pipe(int *status, t_data *data)
{
	static int	count;

	ft_pipe(data->pipe_arr[count]);
	count++;
	*status = DO_FORK;
}
