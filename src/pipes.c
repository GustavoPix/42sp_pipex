/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:37:29 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/21 13:27:27 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void pipe_start(char *file_read, int **fd)
{
    printf("Pid1\n");
    int fdFile;
    fdFile = open(file_read, O_RDONLY);
    dup2(fdFile, STDIN_FILENO);
    close(fdFile);
    dup2(fd[1][1], STDOUT_FILENO);
    close(fd[0][1]);
    close(fd[2][0]);
    close(fd[1][0]);
    close(fd[2][1]);
    char *argVec[] = {"./test/start_file", "1", NULL};
    char * envVec[] = {NULL};
    if(execve("/usr/bin/grep", argVec, envVec) == -1)
        perror("Grep error");
}

