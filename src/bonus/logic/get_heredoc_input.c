/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:29 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 15:24:06 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"
#include <sys/fcntl.h>
#include <unistd.h>

static char	*get_rand_name(void)
{
	//access로ㅗ 있으면 다른걸로 오푼
	return (ft_strdup("temp"));
}

static int	get_heredoc_fd(char **envp, char *heredoc_filename)
{
	int		heredoc_fd;
	char	**path_vector;
	char	*mktemp_cmd;
	char	**mktemp_cmd_vector;
	int		pipe_ret;
	pid_t	fork_ret;
	int		child_status;
	int		child_exit_status;
	int		fd[2];

	path_vector = get_path_vector(envp);
	mktemp_cmd = get_cmd_path("mktemp", path_vector);
	if (mktemp_cmd == INVALID_PATH)
	{
		heredoc_filename = get_rand_name();
		heredoc_fd = open(heredoc_filename, O_WRONLY | O_CREAT, 0644);
		//unlink(heredoc_filename);
		return (heredoc_fd);
	}
	mktemp_cmd_vector = ft_split(mktemp_cmd, '\0');
	pipe_ret = pipe(fd);
	if (pipe_ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	fork_ret = fork();
	if (fork_ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	else if (fork_ret == 0)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		execve(mktemp_cmd, mktemp_cmd_vector, envp);
	}
	close(fd[WRITE_END]);
	waitpid(fork_ret, &child_status, 0);
	child_exit_status = wexitstatus(child_status);
	if (child_exit_status != 0)
	{
		ft_putendl_fd("mktemp failure", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	heredoc_filename = get_next_line(fd[READ_END]);
	if (heredoc_filename[ft_strlen(heredoc_filename) - 1] == '\n')
		heredoc_filename[ft_strlen(heredoc_filename) - 1] = '\0';
	heredoc_fd = open(heredoc_filename, O_WRONLY);
	//unlink(heredoc_filename);
	return (heredoc_fd);
}

void	get_heredoc_input(t_data *data)
{
	char	*line;

	data->heredoc_fd = get_heredoc_fd(data->argset.envp, data->heredoc_filename);
	printf("data->heredoc_fd = %d\n", data->heredoc_fd);
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		line = get_next_line(STDOUT_FILENO);
		printf("line = %s", line);
		if (ft_strncmp(line, data->filename.limiter, ft_strlen(line) - 1) == 0)
			break ;
		write(data->heredoc_fd, line, ft_strlen(line));
	}
	close(data->heredoc_fd);
	data->heredoc_fd = open(data->heredoc_filename, O_RDONLY);
	data->status = ALLOCATE_PIPE;
}
