/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:53:21 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/08 20:28:06 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static void	execute_first_cmd(const int *right_pipe, char *infile, t_cmd first_cmd, char **envp)
{
	int	infile_fd;

	close(right_pipe[READ_END]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	if (first_cmd.cmd_path == INVALID_PATH)
	{
		ft_putendl_fd("bash: command not found", STDERR_FILENO);
		exit(COMMAND_NOT_FOUND);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(right_pipe[WRITE_END], STDOUT_FILENO);
	close(right_pipe[WRITE_END]);
	execve(first_cmd.cmd_path, first_cmd.cmd_vector, envp);
}

static void	execute_last_cmd(const int *left_pipe, char *outfile, t_cmd last_cmd, char **envp)
{
	int	outfile_fd;

	close(left_pipe[WRITE_END]);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	if (last_cmd.cmd_path == INVALID_PATH)
	{
		ft_putendl_fd("bash: command not found", STDERR_FILENO);
		exit(COMMAND_NOT_FOUND);
	}
	dup2(left_pipe[READ_END], STDIN_FILENO);
	close(left_pipe[READ_END]);
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
		ft_putendl_fd("bash: command not found", STDERR_FILENO);
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

	if (data->cur_process_index == 0)
		execute_first_cmd(right_pipe, data->filename.in, data->cmd_arr[data->cur_process_index], data->argset.envp);
	else if (data->cur_process_index == data->total_cmd - 1)
		execute_last_cmd(left_pipe, data->filename.out, data->cmd_arr[data->cur_process_index], data->argset.envp);
	else
		execute_middle_cmds(left_pipe, right_pipe, data->cmd_arr[data->cur_process_index], data->argset.envp);
}
