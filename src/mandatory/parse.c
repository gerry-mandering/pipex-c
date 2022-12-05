/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:56:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 10:27:41 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	parse_filename(t_data *data, char **av)
{
	data->in_file = av[1];
	data->out_file = av[4];
}

static void	parse_command(t_data *data, char **av)
{
	data->fst_cmd_vector = ft_split(av[2], ' ');
	data->lst_cmd_vector = ft_split(av[3], ' ');
	data->fst_cmd = data->fst_cmd_vector[0];
	data->lst_cmd = data->lst_cmd_vector[0];
}

static void	parse_path_vector(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == envp[i])
		{
			data->path_vector = ft_split(&envp[i][5], ':');
			return ;
		}
		i++;
	}
	data->path_vector = NULL;
	return ;
}

void	parse(int *status, t_data *data, char **av, char **envp)
{
	parse_filename(data, av);
	parse_command(data, av);
	parse_path_vector(data, envp);
	*status = SET_PIPE;
}
