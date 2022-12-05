/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:19:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 11:23:24 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	check_args_count(int *status, int ac)
{
	if (ac != 5)
		ft_exit("wrong arguments count", EXIT_FAILURE);
	*status = PARSE;
}

static void	set_pipe(int *status, t_data *data)
{
	int	return_value;

	return_value = pipe(data->fd);
	if (return_value == -1)
		ft_exit("pipe error", EXIT_FAILURE);
	*status = DO_FORK;
}

static void	do_fork(int *status, t_data *data)
{
	int	return_value;

	return_value = fork();
	if (return_value == -1)
		ft_exit("fork error", EXIT_FAILURE);
	else if (return_value == 0)
	{
		*status = FST_CHILD_PROCESS;
		return ;
	}
	data->fst_child_pid = return_value;
	return_value = fork();
	if (return_value == -1)
		ft_exit("fork error", EXIT_FAILURE);
	else if (return_value == 0)
	{
		*status = LST_CHILD_PROCESS;
		return ;
	}
	else
	{
		close(data->fd[0]);
		close(data->fd[1]);
		data->lst_child_pid = return_value;
		*status = PARENT_PROCESS;
		return ;
	}
}

static void	wait_child_process(int *status, t_data *data)
{
	int	lst_child_status;

	waitpid(data->fst_child_pid, NULL, 0);
	waitpid(data->lst_child_pid, &lst_child_status, 0);
	data->exit_status = wexitstatus(lst_child_status);
	*status = EXIT;
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	t_data	data;

	status = CHECK_ARGS_COUNT;
	while (1)
	{
		if (status == CHECK_ARGS_COUNT)
			check_args_count(&status, ac);
		else if (status == PARSE)
			parse(&status, &data, av, envp);
		else if (status == SET_PIPE)
			set_pipe(&status, &data);
		else if (status == DO_FORK)
			do_fork(&status, &data);
		else if (status == PARENT_PROCESS)
			wait_child_process(&status, &data);
		else if (status == FST_CHILD_PROCESS)
			execute_fst_cmd(&data, envp);
		else if (status == LST_CHILD_PROCESS)
			execute_lst_cmd(&data, envp);
		else if (status == EXIT)
			exit(data.exit_status);
	}
}
