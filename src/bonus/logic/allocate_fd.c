/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:43:58 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/06 17:47:17 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	allocate_fd(t_data *data)
{
	int	i;

	data->fd = (int **)ft_calloc(data->total_cmd, sizeof(int *));
	i = 0;
	while (i < data->total_cmd)
		data->fd[i++] = (int *)ft_calloc(2, sizeof(int));
}
