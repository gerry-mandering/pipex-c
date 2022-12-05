/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:14:53 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 09:45:13 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*get_cmd_path(t_data *data, char *cmd)
{
	int		i;
	char	*path;
	char	*cmd_path;

	i = 0;
	while (data->path_vector != NULL && data->path_vector[i])
	{
		path = ft_strjoin(data->path_vector[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		ft_free(path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_free(cmd_path);
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	ft_putendl_fd("bash: command not found", STDERR_FILENO);
	exit(127);
	return (NULL);
}

void	dup2_and_close_oldfd(int oldfd, int newfd)
{
	int	return_value;

	return_value = dup2(oldfd, newfd);
	if (return_value == -1)
		ft_exit(NULL, EXIT_FAILURE);
	close(oldfd);
}

int	wexitstatus(int status)
{
	return ((int)(((unsigned)(status) >> 8) & 0xff));
}
