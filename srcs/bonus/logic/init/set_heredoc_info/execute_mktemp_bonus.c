/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mktemp_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:40:29 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 19:04:48 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../includes/pipex_bonus.h"

static char	*read_filename_from_pipe(pid_t ret, int fd[2])
{
	char	*filename;
	int		len;
	int		wstatus;

	waitpid(ret, &wstatus, 0);
	if (wexitstatus(wstatus) != 0)
	{
		ft_putendl_fd("mktemp failure", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	filename = get_next_line(fd[READ_END]);
	len = ft_strlen(filename);
	if (filename[len - 1] == '\n')
		filename[len - 1] = '\0';
	return (filename);
}

char	*execute_mktemp(char *mktemp_path, char **envp)
{
	char	*filename;
	char	**mktemp_vector;
	int		fd[2];
	pid_t	ret;

	mktemp_vector = ft_split(mktemp_path, '\0');
	ft_pipe(fd);
	ret = ft_fork();
	if (ret == 0)
	{
		ft_close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		ft_close(fd[WRITE_END]);
		execve(mktemp_path, mktemp_vector, envp);
	}
	ft_close(fd[WRITE_END]);
	filename = read_filename_from_pipe(ret, fd);
	ft_free(mktemp_path);
	free_path_vector((const char **)mktemp_vector);
	return (filename);
}
