/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 19:56:23 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/18 20:30:21 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_remove_reft(char const *str, char const *set)
{
	int	i;
	int	iset;

	i = 0;
	iset = 0;
	while (str[i])
	{
		while (set[iset])
		{
			if (str[i] == set[iset])
			{
				i++;
				iset = -1;
			}
			iset++;
		}
		return (i);
	}
	return (i);
}

static int	to_remove_right(char const *str, char const *set)
{
	int	i;
	int	iset;

	i = ft_strlen(str) - 1;
	iset = 0;
	while (str[i] && i > 0)
	{
		while (set[iset])
		{
			if (str[i] == set[iset])
			{
				i--;
				iset = -1;
			}
			iset++;
		}
		return (i + 1);
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*aux;
	unsigned int	lremove;
	unsigned int	rremove;
	int				i;

	lremove = to_remove_reft(s1, set);
	if (lremove >= ft_strlen(s1))
	{
		aux = malloc(1 * sizeof(char));
		aux[0] = '\0';
		return (aux);
	}
	rremove = to_remove_right(s1, set);
	i = 0;
	aux = malloc((rremove - lremove + 1) * sizeof(char));
	if (!aux)
		return (NULL);
	while (s1[i + lremove] && i + lremove < rremove)
	{
		aux[i] = s1[i + lremove];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
