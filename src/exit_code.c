/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:06:29 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 10:10:36 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_code_file(t_data *data)
{
	if (check_read_file(data->file_open) == -2 || check_write_file(data->file_exit) == 0)
		data->status = 1;
	if (access(data->file_exit, F_OK) < 0)
	{
		int fd = open(data->file_exit, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		ft_putstr_fd("",fd);
		close(fd);
	}
}

void	errcmd_ext_code(t_data *data, char *cmd)
{
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	data->status = 127;
}
