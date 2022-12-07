/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:41:18 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 09:52:57 by minseok2         ###   ########.fr       */
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

//define current status
# define PARSE				0
# define ALLOCATE_FD		1
# define ALLOCATE_PID_ARR	2
# define SET_PIPE			3
# define DO_FORK			4
# define PARENT_WAITING		5
# define CHILD_EXECUTE		6
# define EXIT				7

//define pipe side
# define READ_END			0
# define WRITE_END			1

//define flag on, off
# define OFF				0
# define ON					1

//define invalid path
# define INVALID_PATH		NULL
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
}	t_cmd;

typedef struct s_data
{
	int					status;
	int					cur_process_index;
	int					heredoc_flag;
	int					exit_status;
	int					total_cmd;
	int					**fd;
	pid_t				*pid_arr;
	struct s_argset		argset;
	struct s_filename	filename;
	struct s_cmd		*cmd_arr;
}	t_data;

//status
void	parse(t_data *data);
t_cmd	*parse_cmd_arr(int *total_cmd, int *heredoc_flag, \
						t_argset *argset);
void	allocate_fd(t_data *data);
void	allocate_pid_arr(t_data *data);
void	set_pipe(t_data *data);
void	do_fork(t_data *data);
void	parent_waiting(t_data *data);

//utils
int		wexitstatus(int status);

#endif
