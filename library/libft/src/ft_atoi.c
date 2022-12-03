/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:30:23 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/03 15:01:04 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#define POS	1
#define NEG	-1

static int	get_sign(char **string)
{
	if (**string == '-')
	{
		(*string)++;
		return (-1);
	}
	else if (**string == '+')
	{
		(*string)++;
		return (1);
	}
	else
		return (1);
}

int	ft_atoi(char *string)
{
	int				i;
	int				sign;
	unsigned long	number;

	i = 0;
	sign = get_sign(&string);
	if ((*string) == '\0')
		ft_exit("Error: ft_atoi", EXIT_FAILURE);
	number = 0;
	while (ft_isspace(*string))
		string++;
	while (string[i])
	{
		if (!(ft_isdigit(string[i])))
			ft_exit("Error: ft_atoi", EXIT_FAILURE);
		number *= 10;
		number += (string[i] - '0');
		if ((sign == POS && number > 2147483647) || \
				(sign == NEG && number > 2147483648))
			ft_exit("Error: ft_atoi", EXIT_FAILURE);
		i++;
	}
	return ((int)(sign * number));
}
