/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_p_util1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:45:10 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:39 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_address_digit(uintptr_t address)
{
	int	address_digit;

	address_digit = 1;
	while (address > 15)
	{
		address /= 16;
		address_digit++;
	}
	return (address_digit);
}

static char	*convert_address_to_string(t_info *info, uintptr_t address)
{
	const char	*hex = "0123456789abcdef";
	char		*address_string;
	int			prefix_len;
	int			address_digit;

	prefix_len = 2;
	address_digit = get_address_digit(address);
	address_string = (char *)malloc(sizeof(char) * \
			(address_digit + prefix_len + 1));
	if (address_string == NULL)
	{
		info->status = ERROR;
		return (NULL);
	}
	address_string[prefix_len + (address_digit--)] = '\0';
	while (address_digit >= 0)
	{
		address_string[prefix_len + (address_digit--)] \
			= hex[address % 16];
		address /= 16;
	}
	address_string[0] = '0';
	address_string[1] = 'x';
	return (address_string);
}

void	init_address_info(t_info *info, t_address_info *address_info, \
		uintptr_t address)
{
	address_info->address = address;
	address_info->address_string = convert_address_to_string(info, address);
	if (info->status == ERROR)
		return ;
	address_info->address_string_len = \
					ft_pf_strlen(address_info->address_string);
}
