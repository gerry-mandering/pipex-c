/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:17:19 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 15:44:39 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex.h"

void	do_fork(int *status, t_data *data)
{
	static int	count;
	pid_t		ret;

	data->cur_cmd = count;
	ret = ft_fork();
	if (ret == 0)
		*status = CHILD_EXECUTE;
	else
	{
		if (data->cur_cmd != 0)
		{
			ft_close(data->pipe_arr[data->cur_cmd - 1][READ_END]);
			ft_close(data->pipe_arr[data->cur_cmd - 1][WRITE_END]);
		}
		data->cmd_arr[data->cur_cmd].pid = ret;
		if (data->cur_cmd == data->total_cmd - 1)
			*status = PARENT_WAITING;
		else if (data->cur_cmd == data->total_cmd - 2)
			*status = DO_FORK;
		else
			*status = SET_PIPE;
		count++;
	}
}
