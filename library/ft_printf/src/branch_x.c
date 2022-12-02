/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:27:05 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:15 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	precising_hex_num(t_info *info, t_hex_num_info *hex_num_info, \
		char *output_x)
{
	char	*precised_hex_num_string;
	int		hex_num_start_index;

	precised_hex_num_string \
		= (char *)malloc(sizeof(char) * (info->precision + 1));
	if (precised_hex_num_string == NULL)
	{
		info->status = ERROR;
		free(output_x);
		free(hex_num_info->hex_num_string);
		return ;
	}
	ft_pf_memset((void *)(precised_hex_num_string), '0', info->precision);
	hex_num_start_index \
		= (info->precision) - (hex_num_info->hex_num_string_len);
	ft_pf_memmove(precised_hex_num_string + hex_num_start_index, \
			hex_num_info->hex_num_string, hex_num_info->hex_num_string_len);
	precised_hex_num_string[info->precision] = '\0';
	free(hex_num_info->hex_num_string);
	hex_num_info->hex_num_string = precised_hex_num_string;
	hex_num_info->hex_num_string_len = ft_pf_strlen(precised_hex_num_string);
	info->status = COMBINE_HEX_PARTS;
}

static void	print_x(t_info *info, int *printed_len, char *output_x)
{
	do_write(info, output_x, info->total_len);
	*printed_len += info->total_len;
	free(output_x);
}

void	branch_x(t_info *info, int *printed_len, unsigned int hex_number, \
		int option)
{
	char			*output_x;
	t_hex_num_info	hex_num_info;

	init_hex_num_info(info, &hex_num_info, hex_number, option);
	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_x(info, &hex_num_info, &output_x);
		else if (info->status == PRECISING_HEX_NUM)
			precising_hex_num(info, &hex_num_info, output_x);
		else if (info->status == COMBINE_HEX_PARTS)
			combine_hex_parts(info, &hex_num_info, output_x, option);
		else if (info->status == PRINT_X)
			print_x(info, printed_len, output_x);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
