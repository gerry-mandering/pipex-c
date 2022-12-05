/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:17:50 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 14:19:28 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

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
	const t_node	*fst_node = data->process_list.head->next;
	int				in_file_fd;
	char			*cmd_path;

	close(data->fd[0][READ_END]);
	in_file_fd = open_in_file(data);
	cmd_path = get_cmd_path(data, fst_node->cmd);
	dup2_and_close_oldfd(in_file_fd, STDIN_FILENO);
	dup2_and_close_oldfd(data->fd[0][WRITE_END], STDOUT_FILENO);
	execve(cmd_path, fst_node->cmd_vector, envp);
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
	const t_node	*lst_node = data->process_list.tail->prev;
	int				out_file_fd;
	char			*cmd_path;

	close(data->fd[(data->ac) - 5][WRITE_END]);
	out_file_fd = open_out_file(data);
	cmd_path = get_cmd_path(data, lst_node->cmd);
	dup2_and_close_oldfd(data->fd[(data->ac) - 5][READ_END], STDIN_FILENO);
	dup2_and_close_oldfd(out_file_fd, STDOUT_FILENO);
	execve(cmd_path, lst_node->cmd_vector, envp);
}

void	execute_mid_cmd(t_data *data, char **envp)
{
	int		i;
	t_node	*cur_node;
	char	*cmd_path;

	close(data->fd[(data->cur_process_node_index) - 1][WRITE_END]);
	i = 0;
	cur_node = data->process_list.head->next;
	while (cur_node->next != NULL)
	{
		if (i == data->cur_process_node_index)
			break ;
		cur_node = cur_node->next;
		i++;
	}
	cmd_path = get_cmd_path(data, cur_node->cmd);
	dup2_and_close_oldfd(data->fd[(data->cur_process_node_index) - 1][READ_END], STDIN_FILENO);
	dup2_and_close_oldfd(data->fd[data->cur_process_node_index][WRITE_END], STDOUT_FILENO);
	execve(cmd_path, cur_node->cmd_vector, envp);
}
