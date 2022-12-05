/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:17:50 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 09:44:57 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	open_in_file(t_data *data)
{
	int	in_file_fd;

	in_file_fd = open(data->in_file, O_RDONLY);
	if (in_file_fd == -1)
		ft_exit(NULL, EXIT_FAILURE);
	return (in_file_fd);
}

void	execute_fst_cmd(t_data *data, char **envp)
{
	int		in_file_fd;
	char	*cmd_path;

	close(data->fd[READ_END]);
	in_file_fd = open_in_file(data);
	cmd_path = get_cmd_path(data, data->fst_cmd);
	dup2_and_close_oldfd(in_file_fd, STDIN_FILENO);
	dup2_and_close_oldfd(data->fd[WRITE_END], STDOUT_FILENO);
	execve(cmd_path, data->fst_cmd_vector, envp);
}

static int	open_out_file(t_data *data)
{
	int	out_file_fd;

	out_file_fd = open(data->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_file_fd == -1)
		ft_exit(NULL, EXIT_FAILURE);
	return (out_file_fd);
}

void	execute_lst_cmd(t_data *data, char **envp)
{
	int		out_file_fd;
	char	*cmd_path;

	close(data->fd[WRITE_END]);
	out_file_fd = open_out_file(data);
	cmd_path = get_cmd_path(data, data->lst_cmd);
	dup2_and_close_oldfd(data->fd[READ_END], STDIN_FILENO);
	dup2_and_close_oldfd(out_file_fd, STDOUT_FILENO);
	execve(cmd_path, data->lst_cmd_vector, envp);
}
