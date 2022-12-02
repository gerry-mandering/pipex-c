/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:21:56 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/02 18:25:40 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd1(t_cmdline *cmdline, int fd[2])
{
	ft_close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execve(cmdline->cmd1.cmd_path, cmdline->cmd1.cmd_vector, cmdline->envp);
}

void	execute_cmd2(t_cmdline *cmdline, int fd[2])
{
	ft_close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(cmdline->outfile_fd, STDOUT_FILENO);
	execve(cmdline->cmd2.cmd_path, cmdline->cmd2.cmd_vector, cmdline->envp);
}

//ft_pipe, ft_fork
int	main(int argc, char **argv, char **envp)
{
	t_cmdline	cmdline;
	int			fd[2];
	int			pid;

	parse(&cmdline, argc, argv, envp);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		execute_cmd1(&cmdline, fd);
	pid = fork();
	if (pid == 0)
		execute_cmd2(&cmdline, fd);
	ft_close(fd[0]);
	ft_close(fd[1]);
	return (0);
}
