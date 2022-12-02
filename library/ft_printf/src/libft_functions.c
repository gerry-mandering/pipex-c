/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:22:16 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/06 00:59:21 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_pf_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

void	*ft_pf_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	character;
	size_t			i;

	ptr = (unsigned char *)b;
	character = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = character;
		i++;
	}
	return (ptr);
}

void	*ft_pf_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = -1;
	if (dest < source)
	{
		while (++i < len)
			dest[i] = source[i];
	}
	else
	{
		while (len > 0)
		{
			dest[len - 1] = source[len - 1];
			len--;
		}
	}
	return (dest);
}

char	*ft_pf_strdup(t_info *info, const char *s1)
{
	char	*str;
	size_t	length;
	size_t	i;

	length = ft_pf_strlen(s1);
	i = 0;
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
	{
		info->status = ERROR;
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
