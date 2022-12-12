/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:24:32 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 17:23:43 by minseok2         ###   ########.fr       */
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

//Status
# define INIT			0
# define SET_PIPE		1
# define DO_FORK		2
# define PARENT_WAITING	3
# define CHILD_EXECUTE	4
# define EXIT			5

//Pipe End
# define READ_END		0
# define WRITE_END		1

//Flag
# define OFF			0
# define ON				1

//Invalid Path
# define INVALID_PATH		NULL

//Exit Status
# define COMMAND_NOT_FOUND	127

typedef struct s_argset
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_argset;

typedef struct s_filename
{
	char	*in;
	char	*out;
}	t_filename;

typedef struct s_heredoc
{
	int		flag;
	int		fd;
	char	*limiter;
	char	*filename;
}	t_heredoc;

typedef struct s_pipe
{
	int	*left;
	int	*right;
}	t_pipe;

typedef struct s_cmd
{
	pid_t			pid;
	char			*cmd;
	char			*path;
	char			**vector;
	int				invalid_path_flag;
	char			*err_msg;
	struct s_pipe	pipe;
}	t_cmd;

typedef struct s_data
{
	int					exit_status;
	int					total_cmd;
	int					cur_cmd;
	int					**pipe_arr;
	struct s_filename	filename;
	struct s_heredoc	heredoc;
	struct s_cmd		*cmd_arr;
}	t_data;

//INIT
void		init(int *status, t_data *data, t_argset *argset);
void		parse_filename(t_data *data, t_argset *argset);
void		set_heredoc_info(t_data *data, t_argset *argset);
char		*make_random_name(void);
char		*execute_mktemp(char *mktemp_path, char **envp);
void		get_heredoc_input(t_data *data);
void		count_total_cmd(t_data *data, t_argset *argset);
void		allocate_pipe_arr(t_data *data);
void		set_cmd_arr(t_data *data, t_argset *argset);

//INIT_UTILS
const char	**get_path_vector(char **envp);
void		free_path_vector(const char **path_vector);
char		*get_cmd_path(char *cmd, const char **path_vector);

//SET_PIPE
void		set_pipe(int *status, t_data *data);

//DO_FORK
void		do_fork(int *status, t_data *data);

//PARENT_WAITING
void		parent_waiting(int *status, t_data *data);

//CHILD_EXECUTE
void		child_execute(t_data *data, char **envp);

//UTILS
int			ft_pipe(int fildes[2]);
pid_t		ft_fork(void);
int			wexitstatus(int status);

#endif
