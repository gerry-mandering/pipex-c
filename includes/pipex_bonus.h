/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:41:18 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 15:22:58 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../library/libft/includes/libft.h"
# include "../library/get_next_line/includes/get_next_line.h"

//define current status
# define PARSE				0
# define GET_HEREDOC_INPUT	1
# define ALLOCATE_PIPE		2
# define ALLOCATE_PID_ARR	3
# define SET_PIPE			4
# define DO_FORK			5
# define PARENT_WAITING		6
# define CHILD_EXECUTE		7
# define EXIT				8

//define pipe side
# define READ_END			0
# define WRITE_END			1

//define flag on, off
# define OFF				0
# define ON					1

//define error
# define INVALID_PATH		NULL

//define exit status
# define COMMAND_NOT_FOUND	127

typedef struct s_argset
{
	int		ac;
	char	**av;
	char	**envp;
}	t_argset;

typedef struct s_filename
{
	char	*in;
	char	*out;
	char	*limiter;
}	t_filename;

typedef struct s_cmd
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_vector;
	char	*err_msg;
}	t_cmd;

typedef struct s_data
{
	int					status;
	int					cur_process_index;
	int					heredoc_flag;
	int					heredoc_fd;
	char				*heredoc_filename;
	int					exit_status;
	int					total_cmd;
	int					**pipe;
	pid_t				*pid_arr;
	struct s_argset		argset;
	struct s_filename	filename;
	struct s_cmd		*cmd_arr;
}	t_data;

void	parse(t_data *data);
t_cmd	*parse_cmd_arr(int *total_cmd, int *heredoc_flag, \
						t_argset *argset);
char	**get_path_vector(char **envp);
char	*get_cmd_path(char *cmd, char **path_vector);

void	get_heredoc_input(t_data *data);

void	allocate_pipe(t_data *data);

void	allocate_pid_arr(t_data *data);

void	set_pipe(t_data *data);

void	do_fork(t_data *data);

void	parent_waiting(t_data *data);

void	child_execute(t_data *data);

//utils
int		wexitstatus(int status);

#endif
