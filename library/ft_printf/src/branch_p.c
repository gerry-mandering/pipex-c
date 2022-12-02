/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:38:27 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:43 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	set_total_len_p(t_info *info, t_address_info *address_info, \
		char **output_p)
{
	if ((info->width) > (address_info->address_string_len))
		info->total_len = info->width;
	else
		info->total_len = address_info->address_string_len;
	*output_p = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_p) == NULL)
	{
		info->status = ERROR;
		free(address_info->address_string);
		return ;
	}
	ft_pf_memset((void *)(*output_p), ' ', info->total_len);
	info->status = SET_ADDRESS_LOCATION;
}

static void	set_address_location(t_info *info, t_address_info *address_info, \
		char *output_p)
{
	int	address_string_location;

	if (info->flags & LEFT)
	{
		address_string_location = 0;
	}
	else
	{
		address_string_location \
			= (info->total_len) - (address_info->address_string_len);
	}
	ft_pf_memmove(output_p + address_string_location, \
			address_info->address_string, address_info->address_string_len);
	free(address_info->address_string);
	info->status = PRINT_P;
}

static void	print_p(t_info *info, int *printed_len, char *output_p)
{
	do_write(info, output_p, info->total_len);
	*printed_len += info->total_len;
	free(output_p);
}

void	branch_p(t_info *info, int *printed_len, uintptr_t address)
{
	char			*output_p;
	t_address_info	address_info;

	init_address_info(info, &address_info, address);
	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_p(info, &address_info, &output_p);
		else if (info->status == SET_ADDRESS_LOCATION)
			set_address_location(info, &address_info, output_p);
		else if (info->status == PRINT_P)
			print_p(info, printed_len, output_p);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
