/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:21:12 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/02 14:21:27 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include <unistd.h>

char	*make_whole_path(char *envpath, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(envpath, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	**parsing_envp(char *envp[])
{
	char	**tmp;
	char	**res;
	int		i;

	i = -1;
	res = NULL;
	while (envp[++i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_split(envp[i], '=');
			res = ft_split(tmp[1], ':');
			free(tmp);
		}
	}
	return (res);
}

char *get_executables(char *cmd, char *paths[])
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (paths[++i])
	{
		cmd_path = make_whole_path(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

typedef struct s_cmd_node
{
	char				*argv;
	char				executables;
	char				*cmd_path;
	char				**args;
} t_cmd_node;

t_cmd_node **parsing_argv(int len, char **argv, char *envp[])
{
	t_cmd_node	**res;
	int			i;

	res = malloc(sizeof(t_cmd_node *) * (len + 1));
	res[len] = NULL;
	i = -1;
	while (++i < len)
	{
		res[i] = malloc(sizeof(t_cmd_node));
		res[i]->argv = argv[i];
		res[i]->args = ft_split(argv[i], ' ');
		res[i]->cmd_path = get_executables(res[i]->args[0], parsing_envp(envp));
		res[i]->executables = 0;
		if (!res[i]->cmd_path)
			res[i]->executables = -1;
	}
	return (res);
}

void	fork_and_execv(t_cmd_node *node, char *envp[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(node->cmd_path, node->args, envp);
	}
}

int main(int argc, char **argv, char *envp[])
{
	t_cmd_node	**cmd_paths;
	int			i;

	if (argc < 2)
	{
		ft_printf("%s \"<cmd>\"..", argv[0]);
		return (1);
	}
	cmd_paths = parsing_argv(argc - 1, argv + 1, envp);
	i = -1;
	while (cmd_paths[++i])
	{
		fork_and_execv(cmd_paths[i], envp);
	}
	i = -1;
	while (++i < argc - 1)
	{
		wait(NULL);
	}
}
