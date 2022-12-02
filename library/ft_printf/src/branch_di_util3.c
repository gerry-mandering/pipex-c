/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_di_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 01:55:32 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:47 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	get_sign_character(t_info *info, t_num_info *num_info)
{
	if (num_info->num < 0)
		return ('-');
	else if (info->flags & PLUS)
		return ('+');
	else
		return (' ');
}

static int	get_sign_location(t_info *info, t_num_info *num_info)
{
	if ((info->flags & LEFT) || (info->flags & ZERO))
		return (0);
	else if ((info->flags & PRECISION) && (info->precision == 0) \
			&& (num_info->num == 0))
		return ((info->total_len) - 1);
	else
		return ((info->total_len) - (num_info->num_string_len) - 1);
}

static int	get_num_string_location(t_info *info, t_num_info *num_info)
{
	if (info->flags & LEFT)
	{
		if ((num_info->num < 0) || (info->flags & PLUS) \
			|| (info->flags & SPACE))
			return (1);
		else
			return (0);
	}
	else
		return ((info->total_len) - (num_info->num_string_len));
}

void	combine_parts(t_info *info, t_num_info *num_info, char *output_di)
{
	int	sign_location;
	int	num_string_location;

	sign_location = get_sign_location(info, num_info);
	num_string_location = get_num_string_location(info, num_info);
	if ((num_info->num < 0) || (info->flags & PLUS) \
			|| (info->flags & SPACE))
		output_di[sign_location] = get_sign_character(info, num_info);
	if (!((info->flags & PRECISION) && (info->precision == 0) \
				&& (num_info->num == 0)))
		ft_pf_memmove(output_di + num_string_location, \
				num_info->num_string, num_info->num_string_len);
	free(num_info->num_string);
	info->status = PRINT_DI;
}
