/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/11 21:08:57 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "./libft/libft.h"

#define BUFFER 256

int test(void)
{
    int fd[3][2];
    int i;

    i = 0;
    while (i < 3)
    {
        if (pipe(fd[i]) < 0)
            return (0);
        i++;
    }

    int pid1 = fork();
    if (pid1 < 0)
        return (0);

    if (pid1 == 0)
    {
        printf("Pid1\n");
        int fdFile;

        fdFile = open("./test/start_file", O_RDONLY);
        dup2(fdFile, STDIN_FILENO);
        close(fdFile);

        // Child process 1 (ping)
        dup2(fd[1][1], STDOUT_FILENO);

        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[1][0]);
        close(fd[2][1]);
        //execlp("ping", "ping", "-c", "5", "google.com", NULL);

        execlp("grep", "grep", "abc", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (0);
    if (pid2 == 0)
    {
            //Child process 2 (grep)
            printf("Pid2\n");
            int fdFile;

            fdFile = open("./test/outfile", O_WRONLY);

            dup2(fd[1][0], STDIN_FILENO);
            dup2(fd[2][1], STDOUT_FILENO);
            close(fd[0][0]);
            close(fd[1][1]);
            close(fd[2][0]);
            close(fd[0][1]);
            //execlp("grep", "grep", "rtt", NULL);
            execlp("wc", "wc", "-w", NULL);

    }

    int pid3 = fork();
    if (pid3 < 0)
        return (0);
    if (pid3 == 0)
    {
            //Child process 2 (grep)
            printf("Pid3\n");
            int fdFile;
            char *aux;

            dup2(fd[2][0], STDIN_FILENO);

            close(fd[1][0]);
            close(fd[2][1]);
            close(fd[0][0]);
            close(fd[1][1]);


            fdFile = open("./test/outfile", O_WRONLY);
            read(STDIN_FILENO,&aux,sizeof(char *));
            //ft_putstr_fd(aux,fdFile);
            //write(1,&aux,1);
            write(fdFile,&aux,1);
            //close(fdFile);
    }

    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][0]);
    close(fd[2][1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    return (0);
}

int main(void)
{
    test();
    return (0);

}

