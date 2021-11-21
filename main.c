/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/21 12:45:24 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int test(void)
{
    int **fd;
    int i;


    i = 0;
    fd = malloc(sizeof(int) * 3);
    while (i < 3)
    {
        fd[i] = malloc(sizeof(int) * 2);
        if (pipe(fd[i]) < 0)
            return (0);
        i++;
    }

    int pid1 = fork();
    if (pid1 < 0)
        return (0);

    if (pid1 == 0)
    {
        pipe_start("./test/start_file",fd);
        //printf("Pid1\n");
        //int fdFile;
//
        //fdFile = open("./test/start_file", O_RDONLY);
        //dup2(fdFile, STDIN_FILENO);
        //close(fdFile);
//
        //// Child process 1 (ping)
        //dup2(fd[1][1], STDOUT_FILENO);
//
        //close(fd[0][1]);
        //close(fd[2][0]);
        //close(fd[1][0]);
        //close(fd[2][1]);
        ////execlp("ping", "ping", "-c", "5", "google.com", NULL);
//
        //execlp("grep", "grep", "abc", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (0);
    if (pid2 == 0)
    {
            //Child process 2 (grep)
            printf("Pid2\n");

            //fdFile = open("./test/outfile", O_WRONLY);

            dup2(fd[1][0], STDIN_FILENO);
            dup2(fd[2][1], STDOUT_FILENO);
            close(fd[0][0]);
            close(fd[1][1]);
            close(fd[2][0]);
            close(fd[0][1]);

            //read(STDIN_FILENO,&aux,10);
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
            aux = ft_calloc(2, sizeof(char));

            dup2(fd[2][0], STDIN_FILENO);

            close(fd[1][0]);
            close(fd[2][1]);
            close(fd[0][0]);
            close(fd[1][1]);

            fdFile = open("./test/outfile", O_WRONLY);
            read(STDIN_FILENO,&aux,2);
            write(fdFile,&aux,2);
    }

    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][0]);
    close(fd[2][1]);
    close(fd[0][1]);
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

