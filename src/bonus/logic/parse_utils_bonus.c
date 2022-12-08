/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:40:58 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/08 19:13:40 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static char	**get_path_vector(char **envp)
{
	char	**path_vector;
	int		i;

	path_vector = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_vector = ft_split(&envp[i][5], ':');
			break ;
		}
		i++;
	}
	return (path_vector);
}

static int	get_cmd_start_index(int *heredoc_flag)
{
	int	cmd_start_index;

	if (*heredoc_flag == ON)
		cmd_start_index = 3;
	else
		cmd_start_index = 2;
	return (cmd_start_index);
}

static char	*get_cmd_path(char *cmd, char **path_vector)
{
	char	*cmd_path;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (path_vector && path_vector[i])
	{
		path = ft_strjoin(path_vector[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		ft_free(path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (INVALID_PATH);
}

t_cmd	*parse_cmd_arr(int *total_cmd, int *heredoc_flag, \
						t_argset *argset)
{
	t_cmd		*cmd_arr;
	char		**path_vector;
	int			cmd_start_index;
	int			i;

	cmd_arr = (t_cmd *)ft_calloc(*total_cmd, sizeof(t_cmd));
	path_vector = get_path_vector(argset->envp);
	cmd_start_index = get_cmd_start_index(heredoc_flag);
	i = 0;
	while (i < *total_cmd)
	{
		cmd_arr[i].cmd_vector = ft_split(argset->av[cmd_start_index + i], ' ');
		cmd_arr[i].cmd = cmd_arr[i].cmd_vector[0];
		cmd_arr[i].cmd_path = get_cmd_path(cmd_arr[i].cmd, path_vector);
		i++;
	}
	return (cmd_arr);
}
