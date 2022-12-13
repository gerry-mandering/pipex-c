/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:20:33 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:15:00 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/pipex.h"

static t_argset	make_argset(int argc, char **argv, char **envp)
{
	t_argset	argset;

	argset.argc = argc;
	argset.argv = argv;
	argset.envp = envp;
	return (argset);
}

int	main(int argc, char **argv, char **envp)
{
	int			status;
	t_data		data;
	t_argset	argset;

	argset = make_argset(argc, argv, envp);
	status = INIT;
	while (1)
	{
		if (status == INIT)
			init(&status, &data, &argset);
		else if (status == SET_PIPE)
			set_pipe(&status, &data);
		else if (status == DO_FORK)
			do_fork(&status, &data);
		else if (status == PARENT_WAITING)
			parent_waiting(&status, &data);
		else if (status == CHILD_EXECUTE)
			child_execute(&data, envp);
		else if (status == EXIT)
			exit(data.exit_status);
	}
}
