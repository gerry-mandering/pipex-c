/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:06:11 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:59:32 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	init_info(t_info *info)
{
	info->status = 0;
	info->total_len = 0;
	info->flags = 0;
	info->width = 0;
	info->precision = 0;
}

static int	end(t_info *info, int return_value)
{
	va_end(info->args);
	return (return_value);
}

int	ft_printf(const char *format, ...)
{
	t_info	info;
	int		printed_len;

	init_info(&info);
	info.format = format;
	va_start(info.args, format);
	printed_len = 0;
	while (1)
	{
		if (info.status == START)
			print_string(&info, &printed_len);
		else if (info.status == PARSE_FLAG)
			parse_flag(&info);
		else if (info.status == PARSE_WIDTH)
			parse_width(&info);
		else if (info.status == PARSE_PRECISION)
			parse_precision(&info);
		else if (info.status == BRANCH_TYPE)
			branch_type(&info, &printed_len);
		else if (info.status == END)
			return (end(&info, printed_len));
		else if (info.status == ERROR)
			return (end(&info, -1));
	}
}
