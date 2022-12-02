/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:15:57 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:57 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	precising_num(t_info *info, t_num_info *num_info, char *output_di)
{
	char	*precised_num_string;
	int		num_start_index;

	precised_num_string = (char *)malloc(sizeof(char) * (info->precision + 1));
	if (precised_num_string == NULL)
	{
		info->status = ERROR;
		free(output_di);
		free(num_info->num_string);
		return ;
	}
	ft_pf_memset((void *)(precised_num_string), '0', info->precision);
	num_start_index = (info->precision) - (num_info->num_string_len);
	ft_pf_memmove(precised_num_string + num_start_index, \
			num_info->num_string, num_info->num_string_len);
	precised_num_string[info->precision] = '\0';
	free(num_info->num_string);
	num_info->num_string = precised_num_string;
	num_info->num_string_len = ft_pf_strlen(precised_num_string);
	info->status = COMBINE_PARTS;
}

static void	print_di(t_info *info, int *printed_len, char *output_di)
{
	do_write(info, output_di, info->total_len);
	*printed_len += info->total_len;
	free(output_di);
}

void	branch_di(t_info *info, int *printed_len, int number)
{
	char		*output_di;
	t_num_info	num_info;

	init_num_info(info, &num_info, number);
	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_di(info, &num_info, &output_di);
		else if (info->status == PRECISING_NUM)
			precising_num(info, &num_info, output_di);
		else if (info->status == COMBINE_PARTS)
			combine_parts(info, &num_info, output_di);
		else if (info->status == PRINT_DI)
			print_di(info, printed_len, output_di);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
