/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_u_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:15:13 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:18 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_precised_u_num_len(t_info *info, t_u_num_info *u_num_info)
{
	if ((info->flags & PRECISION) && (info->precision == 0) \
				&& (u_num_info->u_num == 0))
		return (0);
	else if ((info->flags & PRECISION) && \
			(info->precision > u_num_info->u_num_string_len))
		return (info->precision);
	else
		return (u_num_info->u_num_string_len);
}

static int	get_total_len(t_info *info, int precised_u_num_len)
{
	if (info->width > precised_u_num_len)
		return (info->width);
	else
		return (precised_u_num_len);
}

void	set_total_len_u(t_info *info, t_u_num_info *u_num_info, \
		char **output_u)
{
	int	precised_u_num_len;

	precised_u_num_len = get_precised_u_num_len(info, u_num_info);
	info->total_len = get_total_len(info, precised_u_num_len);
	*output_u = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_u) == NULL)
	{
		info->status = ERROR;
		free(u_num_info->u_num_string);
		return ;
	}
	if (info->flags & ZERO)
		ft_pf_memset((void *)(*output_u), '0', info->total_len);
	else
		ft_pf_memset((void *)(*output_u), ' ', info->total_len);
	if ((info->flags & PRECISION) && \
			(info->precision > u_num_info->u_num_string_len))
		info->status = PRECISING_U_NUM;
	else
		info->status = SET_U_NUM_LOCATION;
}
