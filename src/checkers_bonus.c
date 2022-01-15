/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:47:25 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 10:48:57 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	check_null_parans(int argc, char **argv)
{
	int	i;
	int	j;
	int	pass;

	i = 0;
	while (i < argc)
	{
		j = 0;
		pass = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != ' ')
			{
				pass = 1;
				break ;
			}
			j++;
		}
		if (!pass)
			return (0);
		i++;
	}
	return (1);
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

int	check_read_file(const char *path)
{
	if (access(path, F_OK) < 0)
		return (-2);
	if (access(path, R_OK) < 0)
		return (-1);
	return (0);
}

int	check_write_file(const char *path)
{
	if (access(path, W_OK) < 0 && access(path, F_OK) == 0)
		return (0);
	return (1);
}

int	check_parans(int argc, char **argv)
{
	if (!check_null_parans(argc, argv))
	{
		ft_putstr_fd("One argument is null\n", 1);
		return (0);
	}
	if (argc < 5)
	{
		ft_putstr_fd("Pipex works using: pipex file_in cmd... file_out\n", 1);
		return (0);
	}
	return (1);
}
