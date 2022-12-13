/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_arr_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:54:08 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:21 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/bonus/pipex_bonus.h"

static int	set_offset(int heredoc_flag)
{
	if (heredoc_flag == ON)
		return (3);
	else
		return (2);
}

static char	*set_err_msg(char *cmd)
{
	char	*parts_right;
	char	*parts_left;
	char	*err_msg;

	parts_right = ft_strjoin(": ", cmd);
	if (ft_strchr(cmd, '/'))
		parts_left = ft_strdup("bash: No such file or directory");
	else
		parts_left = ft_strdup("bash: Command not found");
	err_msg = ft_strjoin(parts_left, parts_right);
	ft_free(parts_right);
	ft_free(parts_left);
	return (err_msg);
}

static t_pipe	share_pipe(int i, int total_cmd, int **pipe_arr)
{
	t_pipe	pipe;

	if (i == 0)
	{
		pipe.left = NULL;
		pipe.right = pipe_arr[i];
	}
	else if (i == total_cmd - 1)
	{
		pipe.left = pipe_arr[i - 1];
		pipe.right = NULL;
	}
	else
	{
		pipe.left = pipe_arr[i - 1];
		pipe.right = pipe_arr[i];
	}
	return (pipe);
}

void	set_cmd_arr(t_data *data, t_argset *argset)
{
	const char	**path_vector = (const char **)get_path_vector(argset->envp);
	const int	offset = set_offset(data->heredoc.flag);
	int			i;
	t_cmd		*cmd_arr;

	data->cmd_arr = (t_cmd *)ft_calloc(data->total_cmd, sizeof(t_cmd));
	cmd_arr = data->cmd_arr;
	i = 0;
	while (i < data->total_cmd)
	{
		cmd_arr[i].vector = ft_split(argset->argv[offset + i], ' ');
		cmd_arr[i].cmd = cmd_arr[i].vector[0];
		cmd_arr[i].path = get_cmd_path(cmd_arr[i].cmd, path_vector);
		if (cmd_arr[i].path == INVALID_PATH)
		{
			cmd_arr[i].invalid_path_flag = ON;
			cmd_arr[i].err_msg = set_err_msg(cmd_arr[i].cmd);
		}
		cmd_arr[i].pipe = share_pipe(i, data->total_cmd, data->pipe_arr);
		i++;
	}
	free_path_vector(path_vector);
}
