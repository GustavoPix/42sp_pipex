/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/09 20:18:59 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER 256

int main(void)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        return (1);
    }

    int pid1 = fork();
    if (pid1 < 0)
    {
        return (2);
    }

    if (pid1 == 0)
    {

        int fdFile;

        fdFile = open("./test/start_file", O_RDONLY);
        dup2(fdFile, STDIN_FILENO);
        close(fdFile);

        // Child process 1 (ping)
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);
        //execlp("ping", "ping", "-c", "5", "google.com", NULL);
        execlp("grep", "grep", "abc", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0)
    {
        return (3);
    }
    if (pid2 == 0)
    {
            //Child process 2 (grep)
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            //execlp("grep", "grep", "rtt", NULL);
            execlp("wc", "wc", "-w", NULL);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
}

