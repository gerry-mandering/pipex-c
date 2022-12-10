/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:53:21 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 17:02:04 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static void	execute_first_cmd(const int *right_pipe, int infile_fd, t_cmd first_cmd, char **envp)
{
	//int	infile_fd;

	printf("1\n");
	close(right_pipe[READ_END]);
	//infile_fd = open(infile, O_RDONLY);
	//if (infile_fd == -1)
	//{
	//	perror("bash");
	//	exit(EXIT_FAILURE);
	//}
	if (first_cmd.cmd_path == INVALID_PATH)
	{
		ft_putendl_fd(first_cmd.err_msg, STDERR_FILENO);
		ft_free(first_cmd.err_msg);
		exit(COMMAND_NOT_FOUND);
	}
	printf("2\n");
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(right_pipe[WRITE_END], STDOUT_FILENO);
	close(right_pipe[WRITE_END]);
	execve(first_cmd.cmd_path, first_cmd.cmd_vector, envp);
}

static void	execute_last_cmd(const int *left_pipe, char *outfile, t_cmd last_cmd, char **envp)
{
	int	outfile_fd;

	printf("3\n");
	close(left_pipe[WRITE_END]);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	printf("4\n");
	if (last_cmd.cmd_path == INVALID_PATH)
	{
		ft_putendl_fd(last_cmd.err_msg, STDERR_FILENO);
		ft_free(last_cmd.err_msg);
		exit(COMMAND_NOT_FOUND);
	}
	printf("5\n");
	dup2(left_pipe[READ_END], STDIN_FILENO);
	printf("6\n");
	close(left_pipe[READ_END]);
	printf("7\n");
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	execve(last_cmd.cmd_path, last_cmd.cmd_vector, envp);
}

static void	execute_middle_cmds(const int *left_pipe, const int *right_pipe, t_cmd cmd, char **envp)
{
	close(left_pipe[WRITE_END]);
	close(right_pipe[READ_END]);
	if (cmd.cmd_path == INVALID_PATH)
	{
		ft_putendl_fd(cmd.err_msg, STDERR_FILENO);
		ft_free(cmd.err_msg);
		exit(COMMAND_NOT_FOUND);
	}
	dup2(left_pipe[READ_END], STDIN_FILENO);
	close(left_pipe[READ_END]);
	dup2(right_pipe[WRITE_END], STDOUT_FILENO);
	close(right_pipe[WRITE_END]);
	execve(cmd.cmd_path, cmd.cmd_vector, envp);
}

void	child_execute(t_data *data)
{
	const int	*left_pipe = data->pipe[data->cur_process_index - 1];
	const int	*right_pipe = data->pipe[data->cur_process_index];

	printf("data->cur_process_index = %d\n", data->cur_process_index);
	if (data->cur_process_index == 0)
	{
		printf("0\n");
		if (data->heredoc_flag == ON)
			execute_first_cmd(right_pipe, data->heredoc_fd, data->cmd_arr[data->cur_process_index], data->argset.envp);
		else
			execute_first_cmd(right_pipe, open(data->filename.in, O_RDONLY), data->cmd_arr[data->cur_process_index], data->argset.envp);
	}
	else if (data->cur_process_index == data->total_cmd - 1)
		execute_last_cmd(left_pipe, data->filename.out, data->cmd_arr[data->cur_process_index], data->argset.envp);
	else
		execute_middle_cmds(left_pipe, right_pipe, data->cmd_arr[data->cur_process_index], data->argset.envp);
}
