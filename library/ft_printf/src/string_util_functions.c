/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:35:04 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:59:13 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	do_write(t_info *info, const char *input, int total_len)
{
	int	written_len;
	int	sum;

	written_len = 0;
	sum = 0;
	while (sum < total_len)
	{
		written_len = write(1, (input + sum), (total_len - sum));
		if (written_len == -1)
		{
			info->status = ERROR;
			return ;
		}
		sum += written_len;
	}
	info->status = END_PRINT;
}

void	print_string(t_info *info, int *printed_len)
{
	int	string_len;

	string_len = 0;
	while ((info->format[string_len]) && (info->format[string_len] != '%'))
		string_len++;
	do_write(info, info->format, string_len);
	if (info->status == ERROR)
		return ;
	info->format += string_len;
	*printed_len += string_len;
	if (*(info->format) == '\0')
		info->status = END;
	else
		info->status = PARSE_FLAG;
}
