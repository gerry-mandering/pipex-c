/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:21:56 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/03 20:14:29 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#define COMMAND_NOT_FOUND	127

void	execute_cmd1(t_cmdline *cmdline, int fd[2], char **envp)
{
	ft_close(fd[0]);
	dup2(cmdline->infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execve(cmdline->cmd1.cmd_path, cmdline->cmd1.cmd_vector, envp);
}

void	execute_cmd2(t_cmdline *cmdline, int fd[2], char **envp)
{
	ft_close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(cmdline->outfile_fd, STDOUT_FILENO);
	execve(cmdline->cmd2.cmd_path, cmdline->cmd2.cmd_vector, envp);
}

//ft_pipe, ft_fork
int	main(int argc, char **argv, char **envp)
{
	t_cmdline	cmdline;
	int			fd[2];
	int			pid1, pid2;
	int			wait_pid1, wait_pid2;
	int			status1, status2;

	parse(&cmdline, argc, argv, envp);
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		if (cmdline.cmd1.cmd_path == NULL)
			return (COMMAND_NOT_FOUND);
		execute_cmd1(&cmdline, fd, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		if (cmdline.cmd2.cmd_path == NULL)
			return (COMMAND_NOT_FOUND);
		execute_cmd2(&cmdline, fd, envp);
	}
	ft_close(fd[0]);
	ft_close(fd[1]);
	wait_pid1 = waitpid(pid1, &status1, 0);
	wait_pid2 = waitpid(pid2, &status2, 0);
	exit(WEXITSTATUS(status2));
	return (0);
}
