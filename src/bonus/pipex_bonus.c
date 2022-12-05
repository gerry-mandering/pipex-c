/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:19:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 14:19:07 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	init_process_list(int *status, t_data *data)
{
	init_list(&data->process_list);
	*status = PARSE;
}

void	allocate_pipes(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = data->ac - 4;
	data->fd = (int **)ft_malloc(sizeof(int *) * size);
	while (i < size)
		data->fd[i++] = (int *)ft_malloc(sizeof(int) * 2);
}

static void	set_pipe(int *status, t_data *data)
{
	static int	pipe_index;
	int			return_value;

	return_value = pipe(data->fd[pipe_index]);
	//printf("data->fd[%d][READ_END] = %d\ndata->fd[%d][WRITE_END] = %d\n", pipe_index, data->fd[pipe_index][READ_END], pipe_index, data->fd[pipe_index][WRITE_END]);
	if (return_value == -1)
		ft_exit("pipe error", EXIT_FAILURE);
	pipe_index++;
	*status = DO_FORK;
}

static t_node	*get_cur_process_node(t_data *data, int cur_process_node_index)
{
	int		i;
	t_node	*cur_node;

	i = 0;
	cur_node = data->process_list.head->next;
	while (cur_node->next != NULL)
	{
		if (i == cur_process_node_index)
			break ;
		cur_node = cur_node->next;
		i++;
	}
	return (cur_node);
}

static void	do_fork(int *status, t_data *data)
{
	static int		cur_process_node_index;
	t_node			*cur_node;
	int				return_value;

	return_value = fork();
	if (return_value == -1)
		ft_exit("fork error", EXIT_FAILURE);
	else if (return_value == 0)
	{
		data->cur_process_node_index = cur_process_node_index;
		if (cur_process_node_index == 0)
			*status = FST_CHILD_PROCESS;
		else if (cur_process_node_index == data->ac - 4)
			*status = LST_CHILD_PROCESS;
		else
			*status = MID_CHILD_PROCESSES;
		return ;
	}
	else
	{
		cur_node = get_cur_process_node(data, cur_process_node_index);
		cur_node->pid = return_value;
		if (cur_process_node_index != 0)
		{
			close(data->fd[cur_process_node_index - 1][READ_END]);
			close(data->fd[cur_process_node_index - 1][WRITE_END]);
		}
		if (cur_process_node_index == data->ac - 4)
			*status = PARENT_PROCESS;
		else if (cur_process_node_index == data->ac - 5)
			*status = DO_FORK;
		else
			*status = SET_PIPE;
		cur_process_node_index++;
		return ;
	}
}

static void	wait_child_process(int *status, t_data *data)
{
	int		lst_child_status;
	t_node	*cur_node;

	cur_node = data->process_list.head->next;
	while (cur_node->next != NULL)
	{
		if (cur_node == data->process_list.tail->prev)
			waitpid(cur_node->pid, &lst_child_status, 0);
		else
			waitpid(cur_node->pid, NULL, 0);
		cur_node = cur_node->next;
	}
	data->exit_status = wexitstatus(lst_child_status);
	*status = EXIT;
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	t_data	data;

	data.ac = ac;
	status = INIT_PROCESS_LIST;
	while (1)
	{
		if (status == INIT_PROCESS_LIST)
		{
			//printf("1 = INIT_PROCESS_LIST\n");
			init_process_list(&status, &data);
		}
		else if (status == PARSE)
		{
			//printf("2 = PARSE\n");
			parse(&status, &data, av, envp);
		}
		else if (status == SET_PIPE)
		{
			//printf("3 = SET_PIPE\n");
			set_pipe(&status, &data);
		}
		else if (status == DO_FORK)
		{
			//printf("4 = DO_FORK\n");
			do_fork(&status, &data);
		}
		else if (status == PARENT_PROCESS)
		{
			//printf("5 = PARENT_PROCESS\n");
			wait_child_process(&status, &data);
		}
		else if (status == FST_CHILD_PROCESS)
		{
			//printf("6 = FST_CHILD_PROCESS\n");
			execute_fst_cmd(&data, envp);
		}
		else if (status == MID_CHILD_PROCESSES)
		{
			//printf("7 = MID_CHILD_PROCESSES\n");
			execute_mid_cmd(&data, envp);
		}
		else if (status == LST_CHILD_PROCESS)
		{
			//printf("8 = LST_CHILD_PROCESS\n");
			execute_lst_cmd(&data, envp);
		}
		else if (status == EXIT)
		{
			//printf("9 = EXIT\n");
			exit(data.exit_status);
		}
	}
}
