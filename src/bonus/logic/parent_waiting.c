/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_waiting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:30:07 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 09:50:28 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	parent_waiting(t_data *data)
{
	const int	last_child = (data->total_cmd - 1);
	int			process_index;
	int			lst_status;

	process_index = 0;
	while (process_index < data->total_cmd)
	{
		if (process_index == last_child)
			waitpid(data->pid_arr[process_index], &lst_status, 0);
		else
			waitpid(data->pid_arr[process_index], NULL, 0);
		process_index++;
	}
	data->exit_status = wexitstatus(lst_status);
	data->status = EXIT;
}
