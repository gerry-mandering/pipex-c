/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:56:20 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/05 13:57:56 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

static void	parse_filename(t_data *data, char **av)
{
	data->in_file = av[1];
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		data->here_doc_flag = 1;
		data->end_text = av[2];
	}
	else
	{
		data->here_doc_flag = 0;
		data->end_text = NULL;
	}
	data->out_file = av[data->ac - 1];
}

static void	parse_command(t_data *data, char **av)
{
	int		i;
	t_node	*node;
	char	**cmd_vector;

	if (data->here_doc_flag)
		i = 3;
	else
		i = 2;
	while (i < data->ac - 1)
	{
		cmd_vector = ft_split(av[i], ' ');
		node = new_node(UNSET, cmd_vector[0], cmd_vector);
		push_tail_side(&data->process_list, node);
		i++;
	}
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
	allocate_pipes(data);
	*status = SET_PIPE;
}
