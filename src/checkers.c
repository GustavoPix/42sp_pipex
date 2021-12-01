/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:47:25 by glima-de          #+#    #+#             */
/*   Updated: 2021/12/01 19:42:41 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check_valid_cmds(t_data *data)
{
	int	i;
	int	ok;

	i = 0;
	ok = 1;
	while (i < data->qpipes && ok)
	{
		if (access(data->cmds->command, F_OK) < 0)
		{
			printf("Pipe %d: command not found\n", i);
			ok = 0;
		}
		i++;
	}
	if (!ok)
		clear_cmds(data);
	return (ok);
}

int	check_parans(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Pipex works using: pipex file_in cmd cmd file_out\n");
		return (0);
	}
	if (access(argv[1], R_OK) < 0)
	{
		printf("Failed to read file\n");
		return (0);
	}
	if (access(argv[argc - 1], W_OK) < 0 && access(argv[argc - 1], F_OK) == 0)
	{
		printf("Failed to write file\n");
		return (0);
	}
	return (1);
}
