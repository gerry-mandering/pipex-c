/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:29:57 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 09:26:09 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static void	close_pipe(int **fd, int pipe_index)
{
	close(fd[pipe_index][READ_END]);
	close(fd[pipe_index][WRITE_END]);
}

static int	set_next_status(int count, int total_cmd)
{
	if (count == total_cmd)
		return (PARENT_WAITING);
	else if (count == total_cmd - 1)
		return (DO_FORK);
	else
		return (SET_PIPE);
}

void	do_fork(t_data *data)
{
	static int	count;
	pid_t		ret;

	ret = fork();
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	else if (ret)
	{
		if (count != 0)
			close_pipe(data->fd, count - 1);
		data->pid_arr[count] = ret;
		count++;
		data->status = set_next_status(count, data->total_cmd);
	}
	else
	{
		data->status = CHILD_EXECUTE;
		data->cur_process_index = count;
	}
}
