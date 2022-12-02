/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_di_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:23:46 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:01:18 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_sign_len(t_info *info, t_num_info *num_info)
{
	if (num_info->num < 0 || info->flags & PLUS || info->flags & SPACE)
		return (1);
	else
		return (0);
}

static int	get_precised_num_len(t_info *info, t_num_info *num_info)
{
	if ((info->flags & PRECISION) && (info->precision == 0) \
				&& (num_info->num == 0))
		return (0);
	else if ((info->flags & PRECISION) && \
			(info->precision > num_info->num_string_len))
		return (info->precision);
	else
		return (num_info->num_string_len);
}

static int	get_total_len(t_info *info, int sign_len, int precised_num_len)
{
	if (info->width > sign_len + precised_num_len)
		return (info->width);
	else
		return (sign_len + precised_num_len);
}

void	set_total_len_di(t_info *info, t_num_info *num_info, \
		char **output_di)
{
	int	sign_len;
	int	precised_num_len;

	sign_len = get_sign_len(info, num_info);
	precised_num_len = get_precised_num_len(info, num_info);
	info->total_len = get_total_len(info, sign_len, precised_num_len);
	*output_di = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_di) == NULL)
	{
		info->status = ERROR;
		free(num_info->num_string);
		return ;
	}
	if (info->flags & ZERO)
		ft_pf_memset((void *)(*output_di), '0', info->total_len);
	else
		ft_pf_memset((void *)(*output_di), ' ', info->total_len);
	if ((info->flags & PRECISION) && \
			(info->precision > num_info->num_string_len))
		info->status = PRECISING_NUM;
	else
		info->status = COMBINE_PARTS;
}
