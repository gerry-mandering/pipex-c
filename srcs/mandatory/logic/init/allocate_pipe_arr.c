/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pipe_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:50:25 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 15:45:09 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/pipex.h"

void	allocate_pipe_arr(t_data *data)
{
	int	i;

	data->pipe_arr = (int **)ft_calloc(data->total_cmd - 1, sizeof(int *));
	i = 0;
	while (i < data->total_cmd - 1)
		data->pipe_arr[i++] = (int *)ft_calloc(2, sizeof(int));
}
