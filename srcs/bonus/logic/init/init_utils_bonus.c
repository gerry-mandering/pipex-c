/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:00:18 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:12 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/bonus/pipex_bonus.h"

const char	**get_path_vector(char **envp)
{
	const char	**path_vector;
	int			path_exist_flag;
	int			i;

	path_exist_flag = OFF;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_exist_flag = ON;
			path_vector = (const char **)ft_split(&envp[i][5], ':');
		}
		i++;
	}
	if (path_exist_flag == ON)
		return (path_vector);
	else
		return (NULL);
}

void	free_path_vector(const char **path_vector)
{
	int	i;

	i = 0;
	while (path_vector[i])
	{
		ft_free((void *)path_vector[i]);
		i++;
	}
	ft_free(path_vector);
}

char	*get_cmd_path(char *cmd, const char **path_vector)
{
	char	*cmd_path;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (path_vector[i])
	{
		path = ft_strjoin(path_vector[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		ft_free(path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_free(cmd_path);
		i++;
	}
	return (INVALID_PATH);
}
