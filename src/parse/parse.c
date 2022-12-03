/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:47:01 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/03 20:12:48 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	parse_file(t_cmdline *cmdline, char **argv)
{
	cmdline->infile = argv[1];
	cmdline->outfile = argv[4];
	cmdline->infile_fd = ft_open(cmdline->infile, O_RDONLY);
	cmdline->outfile_fd = open(cmdline->outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

static void	parse_envp(t_cmdline *cmdline, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == envp[i])
		{
			cmdline->envp = ft_split(&envp[i][5], ':');
			return ;
		}
		i++;
	}
	ft_exit("bash: command not found", EXIT_FAILURE);
}

static char	*get_cmd_path(t_cmdline *cmdline, char *cmd)
{
	int		i;
	char	*path;
	char	*cmd_path;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (cmdline->envp[i])
	{
		path = ft_strjoin(cmdline->envp[i], "/");
		//할당!!!!!
		cmd_path = ft_strjoin(path, cmd);
		ft_free(path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		ft_free(cmd_path);
		i++;
	}
	perror("bash: command not found");
	//ft_exit("bash: command not found", EXIT_FAILURE);
	return (NULL);
}

static void	parse_cmd(t_cmdline *cmdline, char **argv)
{
	char	**cmd1_vector;
	char	**cmd2_vector;

	//할당!!!
	cmd1_vector = ft_split(argv[2], ' ');
	cmd2_vector = ft_split(argv[3], ' ');
	cmdline->cmd1.cmd_path = get_cmd_path(cmdline, cmd1_vector[0]);
	cmdline->cmd1.cmd_vector = cmd1_vector;
	cmdline->cmd2.cmd_path = get_cmd_path(cmdline, cmd2_vector[0]);
	cmdline->cmd2.cmd_vector = cmd2_vector;
}

//cmd_loc 저장해놓으면 굳이 envp필요없음
void	parse(t_cmdline *cmdline, int argc, char **argv, char **envp)
{
	if (argc != 5)
		ft_exit("wrong arguments count", EXIT_FAILURE);
	parse_file(cmdline, argv);
	parse_envp(cmdline, envp);
	parse_cmd(cmdline, argv);
}
