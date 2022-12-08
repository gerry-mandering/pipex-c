/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pid_arr_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:13:16 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/08 12:58:01 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	allocate_pid_arr(t_data *data)
{
	data->pid_arr = (pid_t *)ft_calloc(data->total_cmd, sizeof(pid_t));
	data->status = SET_PIPE;
}
