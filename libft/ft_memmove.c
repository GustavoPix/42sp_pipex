/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 09:50:30 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 09:50:41 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
