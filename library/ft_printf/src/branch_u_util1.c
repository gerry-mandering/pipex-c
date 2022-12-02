/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_u_util1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:56:52 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:23 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_u_num_digit(unsigned int u_number)
{
	int	digit;

	digit = 1;
	while (u_number > 9)
	{
		u_number /= 10;
		digit++;
	}
	return (digit);
}

static char	*convert_unsigned_int_to_string(t_info *info, unsigned int u_number)
{
	const char	*ten_digit = "0123456789";
	char		*u_num_string;
	int			digit;

	digit = get_u_num_digit(u_number);
	u_num_string = (char *)malloc(sizeof(char) * (digit + 1));
	if (u_num_string == NULL)
	{
		info->status = ERROR;
		return (NULL);
	}
	u_num_string[digit--] = '\0';
	while (digit >= 0)
	{
		u_num_string[digit--] = ten_digit[u_number % 10];
		u_number /= 10;
	}
	return (u_num_string);
}

void	init_u_num_info(t_info *info, t_u_num_info *u_num_info, \
		unsigned int u_number)
{
	u_num_info->u_num = u_number;
	u_num_info->u_num_string = convert_unsigned_int_to_string(info, u_number);
	if (info->status == ERROR)
		return ;
	u_num_info->u_num_string_len = ft_pf_strlen(u_num_info->u_num_string);
}
