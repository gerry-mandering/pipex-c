/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_waiting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:27:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 09:54:32 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	parent_waiting(int *status, t_data *data)
{
	const pid_t	last_child_pid = data->cmd_arr[data->total_cmd - 1].pid;
	int			wstatus;
	int			i;

	i = 0;
	while (i < data->total_cmd)
	{
		if (data->cmd_arr[i].pid == last_child_pid)
			waitpid(data->cmd_arr[i].pid, &wstatus, 0);
		else
			waitpid(data->cmd_arr[i].pid, NULL, 0);
		i++;
	}
	data->exit_status = wexitstatus(wstatus);
	*status = EXIT;
}
