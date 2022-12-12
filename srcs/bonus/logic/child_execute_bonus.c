/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:37:41 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 16:44:54 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static void	execute(int read_end, int write_end, t_cmd *cmd, char **envp)
{
	if (cmd->invalid_path_flag == ON)
	{
		ft_putendl_fd(cmd->err_msg, STDERR_FILENO);
		ft_free(cmd->err_msg);
		exit(COMMAND_NOT_FOUND);
	}
	dup2(read_end, STDIN_FILENO);
	ft_close(read_end);
	dup2(write_end, STDOUT_FILENO);
	ft_close(write_end);
	execve(cmd->path, cmd->vector, envp);
}

static void	execute_first_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	int		read_end;

	ft_close(cmd->pipe.right[READ_END]);
	if (data->heredoc.flag == ON)
		read_end = data->heredoc.fd;
	else
		read_end = open(data->filename.in, O_RDONLY);
	if (read_end == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	unlink(data->heredoc.filename);
	execute(read_end, cmd->pipe.right[WRITE_END], cmd, envp);
}

static void	execute_last_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	int	write_end;
	int	oflag;

	ft_close(cmd->pipe.left[WRITE_END]);
	if (data->heredoc.flag == ON)
		oflag = O_WRONLY | O_APPEND | O_CREAT;
	else
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	write_end = open(data->filename.out, oflag, 0644);
	if (write_end == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	execute(cmd->pipe.left[READ_END], write_end, cmd, envp);
}

static void	execute_middle_cmd(t_cmd *cmd, char **envp)
{
	ft_close(cmd->pipe.left[WRITE_END]);
	ft_close(cmd->pipe.right[READ_END]);
	execute(cmd->pipe.left[READ_END], cmd->pipe.right[WRITE_END], cmd, envp);
}

void	child_execute(t_data *data, char **envp)
{
	t_cmd	*cmd;

	cmd = &data->cmd_arr[data->cur_cmd];
	if (data->cur_cmd == 0)
		execute_first_cmd(data, cmd, envp);
	else if (data->cur_cmd == data->total_cmd - 1)
		execute_last_cmd(data, cmd, envp);
	else
		execute_middle_cmd(cmd, envp);
}
