/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_x_util3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:34:58 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:03 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_prefix_location(t_info *info, t_hex_num_info *hex_num_info)
{
	int	prefix_len;

	prefix_len = 2;
	if ((info->flags & LEFT) || (info->flags & ZERO))
		return (0);
	else
		return ((info->total_len) - (hex_num_info->hex_num_string_len) \
				- prefix_len);
}

static int	get_hex_num_string_location(t_info *info, \
		t_hex_num_info *hex_num_info)
{
	if (info->flags & LEFT)
	{
		if ((info->flags & HASH) && (hex_num_info->hex_num != 0))
			return (2);
		else
			return (0);
	}
	else
		return ((info->total_len) - (hex_num_info->hex_num_string_len));
}

void	combine_hex_parts(t_info *info, t_hex_num_info *hex_num_info, \
		char *output_x, int option)
{
	char	*prefix;
	int		prefix_location;
	int		hex_num_string_location;

	if (option == LOWER)
		prefix = "0x";
	else
		prefix = "0X";
	prefix_location = get_prefix_location(info, hex_num_info);
	hex_num_string_location = get_hex_num_string_location(info, hex_num_info);
	if ((info->flags & HASH) && (hex_num_info->hex_num != 0))
		ft_pf_memmove(output_x + prefix_location, prefix, 2);
	if (!((info->flags & PRECISION) && (info->precision == 0) \
				&& (hex_num_info->hex_num == 0)))
		ft_pf_memmove(output_x + hex_num_string_location, \
				hex_num_info->hex_num_string, hex_num_info->hex_num_string_len);
	free(hex_num_info->hex_num_string);
	info->status = PRINT_X;
}
