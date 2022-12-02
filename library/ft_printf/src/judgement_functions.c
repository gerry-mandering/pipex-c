/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judgement_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:05:34 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:59:25 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	is_flag(char character)
{
	if (character == '0' || character == '+' || character == ' ' \
			|| character == '-' || character == '#')
		return (1);
	else
		return (0);
}

int	is_numeric(char character)
{
	if (character >= '0' && character <= '9')
		return (1);
	else
		return (0);
}

int	is_precision(char character)
{
	if (character == '.')
		return (1);
	else
		return (0);
}
