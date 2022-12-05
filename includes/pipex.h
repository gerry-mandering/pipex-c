/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:16:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 10:27:53 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../library/libft/includes/libft.h"

//define pipe read_end, write_end side
# define READ_END			0
# define WRITE_END			1

//define "command not found" exit status
# define COMMAND_NOT_FOUND	127

//define status
# define CHECK_ARGS_COUNT	0
# define PARSE				1
# define SET_PIPE			2
# define DO_FORK			3
# define PARENT_PROCESS		4
# define FST_CHILD_PROCESS	5
# define LST_CHILD_PROCESS	6
# define EXIT				7

typedef struct s_data
{
	int		fd[2];
	char	*in_file;
	char	*out_file;
	int		fst_child_pid;
	int		lst_child_pid;
	char	*fst_cmd;
	char	*lst_cmd;
	char	**fst_cmd_vector;
	char	**lst_cmd_vector;
	char	**path_vector;
	int		exit_status;
}	t_data;

void	parse(int *status, t_data *data, char **av, char **envp);
int		wexitstatus(int status);
char	*get_cmd_path(t_data *data, char *cmd);
void	dup2_and_close_oldfd(int oldfd, int newfd);
void	execute_fst_cmd(t_data *data, char **envp);
void	execute_lst_cmd(t_data *data, char **envp);

#endif
