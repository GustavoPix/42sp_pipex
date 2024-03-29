/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:10:28 by glima-de          #+#    #+#             */
/*   Updated: 2021/12/02 19:05:03 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *s)
{
	char	*aux;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	aux = malloc((i + 1) * sizeof(char));
	i = 0;
	while (s[i])
	{
		aux[i] = s[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
