/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_total_cmd_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:48:19 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:00 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/bonus/pipex_bonus.h"

void	count_total_cmd(t_data *data, t_argset *argset)
{
	if (data->heredoc.flag == ON)
		data->total_cmd = argset->argc - 4;
	else
		data->total_cmd = argset->argc - 3;
}
