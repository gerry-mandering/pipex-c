/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_fd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:43:58 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/10 15:50:35 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	allocate_pipe(t_data *data)
{
	int	i;

	printf("total_cmd = %d\n", data->total_cmd);
	data->pipe = (int **)ft_calloc(data->total_cmd, sizeof(int *));
	i = 0;
	while (i < data->total_cmd)
		data->pipe[i++] = (int *)ft_calloc(2, sizeof(int));
	data->status = ALLOCATE_PID_ARR;
}
