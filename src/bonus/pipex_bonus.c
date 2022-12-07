/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:26:45 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 17:07:43 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	init_argset(t_data *data, int ac, char **av, char **envp)
{
	data->argset.ac = ac;
	data->argset.av = av;
	data->argset.envp = envp;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	init_argset(&data, ac, av, envp);
	data.status = PARSE;
	while (1)
	{
		if (data.status == PARSE)
			parse(&data);
		else if (data.status == ALLOCATE_FD)
			allocate_fd(&data);
		else if (data.status == ALLOCATE_PID_ARR)
			allocate_pid_arr(&data);
		else if (data.status == SET_PIPE)
			set_pipe(&data);
		else if (data.status == DO_FORK)
			do_fork(&data);
		else if (data.status == PARENT_WAITING)
			parent_waiting(&data);
		else if (data.status == CHILD_EXECUTE)
			child_execute(&data);
		else if (data.status == EXIT)
			exit(data.exit_status);
	}
}
