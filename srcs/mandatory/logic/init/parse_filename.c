/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:37:07 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:16:00 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/mandatory/pipex.h"

void	parse_filename(t_data *data, t_argset *argset)
{
	data->filename.in = argset->argv[1];
	data->filename.out = argset->argv[argset->argc - 1];
}
