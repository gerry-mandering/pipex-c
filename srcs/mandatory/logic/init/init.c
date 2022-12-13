/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:31:18 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:15:53 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/mandatory/pipex.h"

void	init(int *status, t_data *data, t_argset *argset)
{
	if (argset->argc != 5)
	{
		ft_putendl_fd("bash: Wrong arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	parse_filename(data, argset);
	count_total_cmd(data, argset);
	allocate_pipe_arr(data);
	set_cmd_arr(data, argset);
	*status = SET_PIPE;
}
