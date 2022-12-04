/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:16:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/04 17:04:53 by minseok2         ###   ########.fr       */
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
# include "../library/ft_printf/includes/ft_printf.h"

# define READ_END			0
# define WRITE_END			1
# define COMMAND_NOT_FOUND	127

typedef struct s_cmd
{
	char	*cmd_path;
	char	**cmd_vector;
}	t_cmd;

typedef struct s_cmdline
{
	char	*infile;
	char	*outfile;
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**envp;
}	t_cmdline;

//parse
void	parse(t_cmdline *cmdline, int argc, char **argv, char **envp);

#endif
