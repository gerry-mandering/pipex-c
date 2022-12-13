/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_info_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:39:12 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:35 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../includes/bonus/pipex_bonus.h"

static char	*create_tmpfile(t_argset *argset)
{
	char		*filename;
	const char	**path_vector = get_path_vector(argset->envp);
	char		*mktemp_path;
	int			fd;

	mktemp_path = get_cmd_path("mktemp", path_vector);
	free_path_vector(path_vector);
	if (mktemp_path == INVALID_PATH)
	{
		filename = make_random_name();
		fd = open(filename, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("bash");
			exit(EXIT_FAILURE);
		}
		ft_close(fd);
		return (filename);
	}
	else
		filename = execute_mktemp(mktemp_path, argset->envp);
	return (filename);
}

void	set_heredoc_info(t_data *data, t_argset *argset)
{
	if (ft_strncmp(data->filename.in, "here_doc", 8))
	{
		data->heredoc.flag = OFF;
		return ;
	}
	data->heredoc.flag = ON;
	data->heredoc.limiter = argset->argv[2];
	data->heredoc.filename = create_tmpfile(argset);
	data->heredoc.fd = open(data->heredoc.filename, O_WRONLY);
	if (data->heredoc.fd == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
}
