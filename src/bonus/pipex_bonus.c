/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:26:45 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 16:58:23 by minseok2         ###   ########.fr       */
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
		{
			printf("-1\n");
			parse(&data);
		}
		else if (data.status == GET_HEREDOC_INPUT)
		{
			printf("-2\n");
			get_heredoc_input(&data);
		}
		else if (data.status == ALLOCATE_PIPE)
		{
			printf("-3\n");
			allocate_pipe(&data);
		}
		else if (data.status == ALLOCATE_PID_ARR)
		{
			printf("-4\n");
			allocate_pid_arr(&data);
		}
		else if (data.status == SET_PIPE)
		{
			printf("-5\n");
			set_pipe(&data);
		}
		else if (data.status == DO_FORK)
		{
			printf("-6\n");
			do_fork(&data);
		}
		else if (data.status == PARENT_WAITING)
		{
			printf("-7\n");
			parent_waiting(&data);
		}
		else if (data.status == CHILD_EXECUTE)
		{
			printf("-8\n");
			child_execute(&data);
		}
		else if (data.status == EXIT)
		{
			printf("-9\n");
			exit(data.exit_status);
		}
	}
}
