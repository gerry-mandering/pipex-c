/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:53:21 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/07 21:17:32 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

static void	execute_first_cmd()
{
//상태 반환 안하므로 순서 고려 x?
}

static void	execute_last_cmd()
{
	//cmd 없을 경우만 127
	//open은 대부분의 경우 실행되지만 open 자체가 실패하는 경우 있을 수 있으므로 127이 우선 순위지 않을까
}

static void	execute_middle_cmds()
{

}

void	child_execute(t_data *data)
{
	if (data->cur_process_index == 0)
		execute_first_cmd();
	else if (data->cur_process_index == data->total_cmd - 1)
		execute_last_cmd();
	else
		execute_middle_cmds();
}
