/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:29:51 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/12 18:56:47 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/pipex.h"

void	get_heredoc_input(t_data *data)
{
	char	*line;
	int		limiter_len;

	if (data->heredoc.flag == OFF)
		return ;
	limiter_len = ft_strlen(data->heredoc.limiter);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->heredoc.limiter, limiter_len) == 0)
		{
			ft_free(line);
			break ;
		}
		write(data->heredoc.fd, line, ft_strlen(line));
		ft_free(line);
	}
	ft_close(data->heredoc.fd);
	data->heredoc.fd = open(data->heredoc.filename, O_RDONLY);
	if (data->heredoc.fd == -1)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
}
