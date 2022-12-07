/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:23:11 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/06 18:27:15 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/pipex_bonus.h"

void	set_pipe(t_data *data)
{
	static int	count;
	int			ret;

	ret = pipe(data->fd[count]);
	if (ret == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	count++;
	data->status = DO_FORK;
}
