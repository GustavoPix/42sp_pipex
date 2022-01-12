/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/12 20:48:24 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

static int	control(t_data *data)
{
	int	i;

	i = 0;
	create_pipes(data);
	while (i < data->qpipes)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (0);
		if (data->pid[i] == 0)
		{
			if (i == 0)
				pipe_start(data);
			else if (i < data->qpipes - 1)
				pipe_middle(data, i);
			else
				pipe_end(data);
			exit (data->status);
		}
		close(data->fd[i][1]);
		waitpid(data->pid[i], &data->status, 0);
		i++;
	}
	clear_data(data);
	return (0);
}

static void	set_params(t_data *data, char *argv, int index)
{
	char	**aux;
	int		args;

	args = 0;
	swap_char_quote(argv, ' ', 1);
	aux = ft_split(argv, ' ');
	while (aux[args])
	{
		swap_char_quote(aux[args], 1, ' ');
		remove_quote(aux[args]);
		args++;
	}
	data->cmds[index].command = ft_strjoin("/", aux[0]);
	data->cmds[index].parans = malloc((args + 1) * sizeof(char *));
	args = 1;
	while (aux[args])
	{
		data->cmds[index].parans[args] = ft_strdup(aux[args]);
		free(aux[args]);
		args++;
	}
	free(aux[0]);
	data->cmds[index].parans[args] = NULL;
	data->cmds[index].parans[0] = "";
	free(aux);
}

static int	get_path(t_data	*data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->path = ft_split(&envp[i][5], ':');
			return (1);
		}
		i++;
	}
	ft_putstr_fd("PATH not found\n", 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	i = 0;
	data.status = 0;
	if (check_parans(argc, argv) == 1)
	{
		data.qpipes = argc - 3;
		data.cmds = malloc(data.qpipes * sizeof(t_commands));
		while (i < data.qpipes)
		{
			set_params(&data, argv[i + 2], i);
			i++;
		}
		if (get_path(&data, envp) && check_valid_cmds(&data))
		{
			data.file_open = argv[1];
			data.file_exit = argv[argc - 1];
			data.pid = (int *)malloc(data.qpipes * sizeof(int));
			control(&data);
		}
	}
	return (data.status);
}
