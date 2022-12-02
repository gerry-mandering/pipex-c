/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:50:19 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:27 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	precising_u_num(t_info *info, t_u_num_info *u_num_info, \
		char *output_u)
{
	char	*precised_u_num_string;
	int		u_num_start_index;

	precised_u_num_string \
		= (char *)malloc(sizeof(char) * (info->precision + 1));
	if (precised_u_num_string == NULL)
	{
		info->status = ERROR;
		free(output_u);
		free(u_num_info->u_num_string);
		return ;
	}
	ft_pf_memset((void *)(precised_u_num_string), '0', info->precision);
	u_num_start_index = (info->precision) - (u_num_info->u_num_string_len);
	ft_pf_memmove(precised_u_num_string + u_num_start_index, \
			u_num_info->u_num_string, u_num_info->u_num_string_len);
	precised_u_num_string[info->precision] = '\0';
	free(u_num_info->u_num_string);
	u_num_info->u_num_string = precised_u_num_string;
	u_num_info->u_num_string_len = ft_pf_strlen(precised_u_num_string);
	info->status = SET_U_NUM_LOCATION;
}

static int	get_u_num_string_location(t_info *info, t_u_num_info *u_num_info)
{
	if (info->flags & LEFT)
		return (0);
	else
		return ((info->total_len) - (u_num_info->u_num_string_len));
}

static void	set_u_num_location(t_info *info, t_u_num_info *u_num_info, \
		char *output_u)
{
	int	u_num_string_location;

	u_num_string_location = get_u_num_string_location(info, u_num_info);
	if (!((info->flags & PRECISION) && (info->precision == 0) \
				&& (u_num_info->u_num == 0)))
		ft_pf_memmove(output_u + u_num_string_location, \
				u_num_info->u_num_string, u_num_info->u_num_string_len);
	free(u_num_info->u_num_string);
	info->status = PRINT_U;
}

static void	print_u(t_info *info, int *printed_len, char *output_u)
{
	do_write(info, output_u, info->total_len);
	*printed_len += info->total_len;
	free(output_u);
}

void	branch_u(t_info *info, int *printed_len, unsigned int u_number)
{
	char			*output_u;
	t_u_num_info	u_num_info;

	init_u_num_info(info, &u_num_info, u_number);
	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_u(info, &u_num_info, &output_u);
		else if (info->status == PRECISING_U_NUM)
			precising_u_num(info, &u_num_info, output_u);
		else if (info->status == SET_U_NUM_LOCATION)
			set_u_num_location(info, &u_num_info, output_u);
		else if (info->status == PRINT_U)
			print_u(info, printed_len, output_u);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
