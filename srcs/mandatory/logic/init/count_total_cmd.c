/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_total_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:48:19 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 15:45:14 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/pipex.h"

void	count_total_cmd(t_data *data, t_argset *argset)
{
	if (data->heredoc.flag == ON)
		data->total_cmd = argset->argc - 4;
	else
		data->total_cmd = argset->argc - 3;
}
