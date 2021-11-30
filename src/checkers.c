/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:47:25 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/30 19:52:32 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
	return (1);
}
