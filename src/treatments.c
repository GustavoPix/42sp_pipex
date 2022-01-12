/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:02:16 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/12 20:48:50 by glima-de         ###   ########.fr       */
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

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	size_t	i;
	char	*pd;
	char	*ps;

	i = 0;
	pd = (char *)destination;
	ps = (char *)source;
	if (pd < ps)
	{
		while (i < num)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	else
	{
		while (num > 0)
		{
			num--;
			pd[num] = ps[num];
		}
	}
	return (destination);
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
