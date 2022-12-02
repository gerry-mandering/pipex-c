/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_di_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:19:59 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:01:14 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_digit(int number)
{
	int	digit;

	digit = 1;
	while (number > 9)
	{
		number /= 10;
		digit++;
	}
	return (digit);
}

static char	*convert_int_to_string(t_info *info, int number)
{
	const char	*ten_digit = "0123456789";
	char		*num_string;
	int			digit;

	if (number == -2147483648)
		return (ft_pf_strdup(info, "2147483648"));
	if (number < 0)
		number *= -1;
	digit = get_digit(number);
	num_string = (char *)malloc(sizeof(char) * (digit + 1));
	if (num_string == NULL)
	{
		info->status = ERROR;
		return (NULL);
	}
	num_string[digit--] = '\0';
	while (digit >= 0)
	{
		num_string[digit--] = ten_digit[number % 10];
		number /= 10;
	}
	return (num_string);
}

void	init_num_info(t_info *info, t_num_info *num_info, int number)
{
	num_info->num = number;
	num_info->num_string = convert_int_to_string(info, number);
	if (info->status == ERROR)
		return ;
	num_info->num_string_len = ft_pf_strlen(num_info->num_string);
}
