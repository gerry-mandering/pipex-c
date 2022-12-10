/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:29:57 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 17:54:05 by minseok2         ###   ########.fr       */
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
	static int	count2;
	pid_t		ret;

	ret = fork();
	printf("ret = %d\n", ret);
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	else if (ret)
	{
		if (count2 == 0)
			close(data->heredoc_fd);
		if (count2 != 0)
			close_pipe(data->pipe, count2 - 1);
		data->pid_arr[count2] = ret;
		count2++;
		data->status = set_next_status(count2, data->total_cmd);
	}
	else
	{
		data->cur_process_index = count2;
		printf("ret = %d\n", ret);
		data->status = CHILD_EXECUTE;
		printf("1data->cur_process_index = %d\n", data->cur_process_index);
	}
}
