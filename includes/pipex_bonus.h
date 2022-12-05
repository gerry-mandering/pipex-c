/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:16:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 13:35:04 by minseok2         ###   ########.fr       */
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
# include "../library/doubly_linked_list/includes/doubly_linked_list.h"

//define PID unset
# define UNSET				0

//define pipe read_end, write_end side
# define READ_END			0
# define WRITE_END			1

//define "command not found" exit status
# define COMMAND_NOT_FOUND	127

//define status
# define INIT_PROCESS_LIST		0
# define PARSE					1
# define SET_PIPE				2
# define DO_FORK				3
# define PARENT_PROCESS			4
# define FST_CHILD_PROCESS		5
# define MID_CHILD_PROCESSES	6
# define LST_CHILD_PROCESS		7
# define EXIT					8

typedef struct s_data
{
	int		here_doc_flag;
	int		ac;
	int		**fd;
	char	*in_file;
	char	*out_file;
	char	*end_text;
	t_list	process_list;
	int		cur_process_node_index;
	char	**path_vector;
	int		exit_status;
}	t_data;

void	parse(int *status, t_data *data, char **av, char **envp);
void	allocate_pipes(t_data *data);
int		wexitstatus(int status);
char	*get_cmd_path(t_data *data, char *cmd);
void	dup2_and_close_oldfd(int oldfd, int newfd);
void	execute_fst_cmd(t_data *data, char **envp);
void	execute_mid_cmd(t_data *data, char **envp);
void	execute_lst_cmd(t_data *data, char **envp);

#endif
