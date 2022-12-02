/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_x_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:32:45 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:06 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_prefix_len(t_info *info, t_hex_num_info *hex_num_info)
{
	if ((info->flags & HASH) && (hex_num_info->hex_num != 0))
		return (2);
	else
		return (0);
}

static int	get_precised_hex_num_len(t_info *info, t_hex_num_info *hex_num_info)
{
	if ((info->flags & PRECISION) && (info->precision == 0) \
				&& (hex_num_info->hex_num == 0))
		return (0);
	else if ((info->flags & PRECISION) && \
			(info->precision > hex_num_info->hex_num_string_len))
		return (info->precision);
	else
		return (hex_num_info->hex_num_string_len);
}

static int	get_total_len(t_info *info, int prefix_len, \
		int precised_hex_num_len)
{
	if (info->width > prefix_len + precised_hex_num_len)
		return (info->width);
	else
		return (prefix_len + precised_hex_num_len);
}

void	set_total_len_x(t_info *info, t_hex_num_info *hex_num_info, \
		char **output_x)
{
	int	prefix_len;
	int	precised_hex_num_len;

	prefix_len = get_prefix_len(info, hex_num_info);
	precised_hex_num_len = get_precised_hex_num_len(info, hex_num_info);
	info->total_len = get_total_len(info, prefix_len, precised_hex_num_len);
	*output_x = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_x) == NULL)
	{
		info->status = ERROR;
		free(hex_num_info->hex_num_string);
		return ;
	}
	if (info->flags & ZERO)
		ft_pf_memset((void *)(*output_x), '0', info->total_len);
	else
		ft_pf_memset((void *)(*output_x), ' ', info->total_len);
	if ((info->flags & PRECISION) && \
			(info->precision > hex_num_info->hex_num_string_len))
		info->status = PRECISING_HEX_NUM;
	else
		info->status = COMBINE_HEX_PARTS;
}
