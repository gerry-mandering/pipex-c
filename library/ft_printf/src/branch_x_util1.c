/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_x_util1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:33:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:11 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_hex_num_digit(unsigned int hex_number)
{
	int	hex_num_digit;

	hex_num_digit = 1;
	while (hex_number > 15)
	{
		hex_number /= 16;
		hex_num_digit++;
	}
	return (hex_num_digit);
}

static char	*convert_hex_num_to_string(t_info *info, unsigned int hex_number, \
		int option)
{
	char		*hex;
	char		*hex_num_string;
	int			hex_num_digit;

	if (option == LOWER)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	hex_num_digit = get_hex_num_digit(hex_number);
	hex_num_string = (char *)malloc(sizeof(char) * \
			(hex_num_digit + 1));
	if (hex_num_string == NULL)
	{
		info->status = ERROR;
		return (NULL);
	}
	hex_num_string[hex_num_digit--] = '\0';
	while (hex_num_digit >= 0)
	{
		hex_num_string[hex_num_digit--] \
			= hex[hex_number % 16];
		hex_number /= 16;
	}
	return (hex_num_string);
}

void	init_hex_num_info(t_info *info, t_hex_num_info *hex_num_info, \
		unsigned int hex_number, int option)
{
	hex_num_info->hex_num = hex_number;
	hex_num_info->hex_num_string \
		= convert_hex_num_to_string(info, hex_number, option);
	if (info->status == ERROR)
		return ;
	hex_num_info->hex_num_string_len = \
					ft_pf_strlen(hex_num_info->hex_num_string);
}
