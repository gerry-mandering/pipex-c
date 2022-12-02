/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:53:03 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:59:17 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	parse_flag(t_info *info)
{
	(info->format)++;
	while (is_flag(*(info->format)))
	{
		if (*(info->format) == '0')
			info->flags |= ZERO;
		else if (*(info->format) == '+')
			info->flags |= PLUS;
		else if (*(info->format) == ' ')
			info->flags |= SPACE;
		else if (*(info->format) == '-')
			info->flags |= LEFT;
		else if (*(info->format) == '#')
			info->flags |= HASH;
		(info->format)++;
	}
	info->status = PARSE_WIDTH;
}

void	parse_width(t_info *info)
{
	while (is_numeric(*(info->format)))
	{
		info->width = (info->width * 10) + (*(info->format) - '0');
		(info->format)++;
	}
	info->status = PARSE_PRECISION;
}

void	parse_precision(t_info *info)
{
	if (is_precision(*(info->format)))
	{
		info->flags |= PRECISION;
		(info->format)++;
	}
	else
	{
		info->status = BRANCH_TYPE;
		return ;
	}
	while (is_numeric(*(info->format)))
	{
		info->precision = (info->precision * 10) + (*(info->format) - '0');
		(info->format)++;
	}
	info->status = BRANCH_TYPE;
}
