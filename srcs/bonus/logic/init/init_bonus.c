/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:31:18 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:08 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/bonus/pipex_bonus.h"

void	init(int *status, t_data *data, t_argset *argset)
{
	if (argset->argc < 5)
	{
		ft_putendl_fd("bash: Wrong arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	parse_filename(data, argset);
	set_heredoc_info(data, argset);
	get_heredoc_input(data);
	count_total_cmd(data, argset);
	allocate_pipe_arr(data);
	set_cmd_arr(data, argset);
	*status = SET_PIPE;
}
