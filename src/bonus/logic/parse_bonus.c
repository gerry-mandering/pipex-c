/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:32:40 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/06 17:41:46 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static t_filename	parse_filename(t_argset *argset)
{
	t_filename	filename;

	filename.in = argset->av[1];
	filename.out = argset->av[argset->ac - 1];
	if (ft_strncmp(filename.in, "here_doc", 8) == 0)
		filename.limiter = argset->av[2];
	else
		filename.limiter = NULL;
	return (filename);
}

static int	set_heredoc_flag(char *limiter)
{
	int	heredoc_flag;

	if (limiter)
		heredoc_flag = ON;
	else
		heredoc_flag = OFF;
	return (heredoc_flag);
}

static int	count_total_cmd(int *heredoc_flag, t_argset *argset)
{
	int	total_cmd;

	if (*heredoc_flag == ON)
		total_cmd = argset->ac - 4;
	else
		total_cmd = argset->ac - 3;
	return (total_cmd);
}

void	parse(t_data *data)
{
	data->filename = parse_filename(&data->argset);
	data->heredoc_flag = set_heredoc_flag(data->filename.limiter);
	data->total_cmd = count_total_cmd(&data->heredoc_flag, &data->argset);
	data->cmd_arr = parse_cmd_arr(&data->total_cmd, &data->heredoc_flag, \
									&data->argset);
	data->status = ALLOCATE_FD;
}
