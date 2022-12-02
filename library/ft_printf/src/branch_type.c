/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:27:02 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:31 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	post_processing_flags(t_info *info)
{
	if (info->flags & ZERO)
	{
		if ((info->flags & PRECISION) || (info->flags & LEFT))
			info->flags &= ~ZERO;
	}
	if (info->flags & SPACE)
	{
		if (info->flags & PLUS)
			info->flags &= ~SPACE;
	}
}

void	branch_type(t_info *info, int *printed_len)
{
	post_processing_flags(info);
	info->status = SET_TOTAL_LEN;
	if (*(info->format) == 'c')
		branch_c(info, printed_len, va_arg(info->args, int));
	else if (*(info->format) == 's')
		branch_s(info, printed_len, va_arg(info->args, char *));
	else if (*(info->format) == 'p')
		branch_p(info, printed_len, va_arg(info->args, uintptr_t));
	else if (*(info->format) == 'd' || *(info->format) == 'i')
		branch_di(info, printed_len, va_arg(info->args, int));
	else if (*(info->format) == 'u')
		branch_u(info, printed_len, va_arg(info->args, unsigned int));
	else if (*(info->format) == 'x')
		branch_x(info, printed_len, va_arg(info->args, unsigned int), LOWER);
	else if (*(info->format) == 'X')
		branch_x(info, printed_len, va_arg(info->args, unsigned int), UPPER);
	else if (*(info->format) == '%')
		branch_c(info, printed_len, '%');
	else
		info->status = ERROR;
	(info->format)++;
}
