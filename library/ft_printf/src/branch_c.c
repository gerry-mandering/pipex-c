/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:26:41 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:57:57 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	set_total_len_c(t_info *info, char **output_c)
{
	if (info->width == 0)
		info->total_len = 1;
	else
		info->total_len = info->width;
	*output_c = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_c) == NULL)
	{
		info->status = ERROR;
		return ;
	}
	ft_pf_memset((void *)(*output_c), ' ', info->total_len);
	info->status = SET_CHARACTER_LOCATION;
}

static void	set_character_location(t_info *info, char character, char *output_c)
{
	if (info->flags & LEFT)
	{
		output_c[0] = character;
	}
	else
	{
		output_c[(info->total_len) - 1] = character;
	}
	info->status = PRINT_C;
}

static void	print_c(t_info *info, int *printed_len, char *output_c)
{
	do_write(info, output_c, info->total_len);
	*printed_len += info->total_len;
	free(output_c);
}

void	branch_c(t_info *info, int *printed_len, char character)
{
	char	*output_c;

	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_c(info, &output_c);
		else if (info->status == SET_CHARACTER_LOCATION)
			set_character_location(info, character, output_c);
		else if (info->status == PRINT_C)
			print_c(info, printed_len, output_c);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
