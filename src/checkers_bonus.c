/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:47:25 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/13 18:37:13 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	test_and_apply_cmd(t_data *data, int index)
{
	int		i;
	int		finded;
	char	*aux;

	i = 0;
	finded = 0;
	while (data->path[i] && !finded)
	{
		aux = ft_strjoin(data->path[i], data->cmds[index].command);
		if (access(aux, F_OK) == 0)
		{
			finded = 1;
			free(data->cmds[index].command);
			data->cmds[index].command = ft_strdup(aux);
		}
		free(aux);
		i++;
	}
	return (finded);
}

int	check_valid_cmds(t_data *data)
{
	int	i;
	int	ok;

	i = 0;
	ok = 1;
	while (i < data->qpipes && ok)
	{
		if (test_and_apply_cmd(data, i) == 0)
		{
			ft_putstr_fd(&data->cmds[i].command[1], 1);
			ft_putstr_fd(": command not found\n", 1);
			ok = 0;
		}
		i++;
	}
	if (!ok)
	{
		clear_cmds(data);
		clear_path(data);
		exit(127);
	}
	return (ok);
}

int	check_parans(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Pipex works using: pipex file_in cmd... file_out\n", 1);
		return (0);
	}
	if (access(argv[1], R_OK) < 0)
	{
		ft_putstr_fd("Failed to read file\n", 1);
		return (0);
	}
	if (access(argv[argc - 1], W_OK) < 0 && access(argv[argc - 1], F_OK) == 0)
	{
		ft_putstr_fd("Failed to write file\n", 1);
		return (0);
	}
	return (1);
}
