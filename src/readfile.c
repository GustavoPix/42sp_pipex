/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:07:48 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/24 20:31:05 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl/get_next_line.h"
#include "../pipex.h"

char *get_text(int fd)
{
    char *aux;
    aux = ft_calloc(100, sizeof(char));
    read(fd,&aux,100);
    return aux;
}
