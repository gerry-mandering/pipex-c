/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:21:56 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/04 17:29:00 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd1(t_cmdline *cmdline, int fd[2], char **envp)
{
	int	infile_fd;

	ft_close(fd[READ_END]);
	infile_fd = open(cmdline->infile, O_RDONLY);
	if (infile_fd == -1)
		ft_exit(NULL, EXIT_FAILURE);
	if (cmdline->cmd1.cmd_path == NULL)
		exit(COMMAND_NOT_FOUND);
	dup2(infile_fd, STDIN_FILENO);
	ft_close(infile_fd);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	ft_close(fd[WRITE_END]);
	execve(cmdline->cmd1.cmd_path, cmdline->cmd1.cmd_vector, envp);
}

void	execute_cmd2(t_cmdline *cmdline, int fd[2], char **envp)
{
	int	outfile_fd;

	ft_close(fd[WRITE_END]);
	outfile_fd = open(cmdline->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		ft_exit(NULL, EXIT_FAILURE);
	if (cmdline->cmd2.cmd_path == NULL)
		exit(COMMAND_NOT_FOUND);
	dup2(fd[READ_END], STDIN_FILENO);
	ft_close(fd[READ_END]);
	dup2(outfile_fd, STDOUT_FILENO);
	ft_close(outfile_fd);
	execve(cmdline->cmd2.cmd_path, cmdline->cmd2.cmd_vector, envp);
}

//ft_pipe, ft_fork
int	main(int argc, char **argv, char **envp)
{
	t_cmdline	cmdline;
	int			fd[2];
	int			pid1, pid2;
	int			wait_pid1, wait_pid2;
	int			final_status;

	parse(&cmdline, argc, argv, envp);
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
		execute_cmd1(&cmdline, fd, envp);
	pid2 = fork();
	if (pid2 == 0)
		execute_cmd2(&cmdline, fd, envp);
	ft_close(fd[0]);
	ft_close(fd[1]);
	wait_pid1 = waitpid(pid1, NULL, 0);
	wait_pid2 = waitpid(pid2, &final_status, 0);
	exit(WEXITSTATUS(final_status));
	return (0);
}
