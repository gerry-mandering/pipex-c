/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:37:49 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 01:00:36 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	set_total_len_s(t_info *info, char *string, char **output_s)
{
	int	string_len;

	string_len = ft_pf_strlen(string);
	if ((info->flags & PRECISION) && (info->precision < string_len))
		info->total_len = info->precision;
	else
		info->total_len = string_len;
	if (info->width > info->total_len)
		info->total_len = info->width;
	*output_s = (char *)malloc(sizeof(char) * (info->total_len));
	if ((*output_s) == NULL)
	{
		info->status = ERROR;
		return ;
	}
	ft_pf_memset((void *)(*output_s), ' ', info->total_len);
	if (info->flags & PRECISION)
		info->status = PRECISING_STRING;
	else
		info->status = SET_STRING_LOCATION;
}

static void	precising_string(t_info *info, char **string, char *output_s)
{
	char	*precised_string;
	int		string_len;
	int		precised_string_len;

	string_len = ft_pf_strlen(*string);
	if (info->precision < string_len)
		precised_string_len = info->precision;
	else
		precised_string_len = string_len;
	precised_string = (char *)malloc(sizeof(char) * (precised_string_len + 1));
	if (precised_string == NULL)
	{
		info->status = ERROR;
		free(output_s);
		return ;
	}
	ft_pf_memmove(precised_string, *string, precised_string_len);
	precised_string[precised_string_len] = '\0';
	*string = precised_string;
	info->status = SET_STRING_LOCATION;
}

static void	set_string_location(t_info *info, char *string, char *output_s)
{
	int	i;
	int	string_len;
	int	start_index;

	i = 0;
	string_len = ft_pf_strlen(string);
	if (info->flags & LEFT)
		start_index = 0;
	else
		start_index = (info->total_len) - string_len;
	while (i < string_len)
		output_s[start_index++] = string[i++];
	if (info->flags & PRECISION)
		free(string);
	info->status = PRINT_S;
}

static void	print_s(t_info *info, int *printed_len, char *output_s)
{
	do_write(info, output_s, info->total_len);
	*printed_len += info->total_len;
	free(output_s);
}

void	branch_s(t_info *info, int *printed_len, char *string)
{
	char	*output_s;

	if (string == NULL)
		string = "(null)";
	while (1)
	{
		if (info->status == SET_TOTAL_LEN)
			set_total_len_s(info, string, &output_s);
		else if (info->status == PRECISING_STRING)
			precising_string(info, &string, output_s);
		else if (info->status == SET_STRING_LOCATION)
			set_string_location(info, string, output_s);
		else if (info->status == PRINT_S)
			print_s(info, printed_len, output_s);
		else if (info->status == END_PRINT)
			break ;
		else if (info->status == ERROR)
			return ;
	}
	init_info(info);
}
