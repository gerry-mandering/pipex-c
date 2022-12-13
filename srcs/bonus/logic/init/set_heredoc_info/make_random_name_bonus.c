/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_random_name_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:41:57 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:30 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../includes/bonus/pipex_bonus.h"

static void	make_concat_str(char *concat_str, unsigned int *buffer)
{
	const char		charset[36] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', \
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', \
		'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};

	concat_str[0] = charset[buffer[0] % 36];
	concat_str[1] = charset[buffer[1] % 36];
	concat_str[2] = charset[buffer[2] % 36];
	concat_str[3] = charset[buffer[3] % 36];
}

char	*make_random_name(void)
{
	char			*filename;
	unsigned int	buffer[4];
	char			concat_str[5];
	int				fd;

	ft_memset(concat_str, 0, sizeof(concat_str));
	fd = open("/dev/urandom", O_RDONLY);
	while (1)
	{
		read(fd, buffer, 4);
		make_concat_str(concat_str, buffer);
		filename = ft_strjoin("tmp.", (const char *)concat_str);
		if (access(filename, F_OK) != 0)
		{
			ft_close(fd);
			return (filename);
		}
		ft_free(filename);
	}
}
