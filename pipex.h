/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:44:14 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 11:17:02 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

/*=============*/
/*  structs    */
/*=============*/
typedef struct s_commands
{
	char	*command;
	char	**parans;
}	t_commands;

typedef struct s_data
{
	char		*file_open;
	char		*file_exit;
	char		**path;
	int			**fd;
	int			qpipes;
	int			*pid;
	int			status;
	t_commands	*cmds;
}	t_data;

/*=============*/
/*  pipes      */
/*=============*/
void			pipe_start(t_data *data);
void			pipe_end(t_data *data);
int				create_pipes(t_data *data);
void			pipe_choose(t_data *data, int index);

/*=============*/
/*  clear      */
/*=============*/
void			clear_data(t_data *data);
void			clear_cmds(t_data *data);
void			clear_path(t_data *data);
void			close_fd(t_data *data, int fdin, int fdout);

/*=============*/
/*  checkers   */
/*=============*/
int				check_parans(int argc, char **argv);
int				check_valid_cmds(t_data *data);
int				check_read_file(const char *path);
int				check_write_file(const char *path);

/*=============*/
/*  treatments */
/*=============*/
void			swap_char_quote(char *str, int from, int to);
void			remove_quote(char *str);
int				test_and_apply_cmd(t_data *data, int index);

/*=============*/
/*  exit_code  */
/*=============*/
void			exit_code_file(t_data *data);
void			errcmd_ext_code(t_data *data, char *cmd);

/*=============*/
/*  libft      */
/*=============*/
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
unsigned int	ft_strlen(const char *str);
void			*ft_memmove(void *destination, const void *source, size_t num);

#endif
