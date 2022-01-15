/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:02:16 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 10:34:08 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	swap_char_quote(char *str, int from, int to)
{
	int	i;
	int	in_quot;

	i = 0;
	in_quot = 0;
	while (str[i] != '\0')
	{
		if (str[i] == from && in_quot)
			str[i] = to;
		else if (str[i] == 39)
			in_quot = !in_quot;
		i++;
	}
}

void	remove_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			if (str[i + 1] != '\0')
			{
				ft_memmove(&str[i], &str[i + 1], ft_strlen(str) - 1);
				str[ft_strlen(str) - 1] = '\0';
			}
			else
				str[i] = '\0';
		}
		i++;
	}
}

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
	if (!finded)
		data->status = 127;
	else
		data->status = 0;
	return (finded);
}
