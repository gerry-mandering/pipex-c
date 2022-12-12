/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:37:07 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 09:53:40 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/pipex_bonus.h"

void	parse_filename(t_data *data, t_argset *argset)
{
	data->filename.in = argset->argv[1];
	data->filename.out = argset->argv[argset->argc - 1];
}
