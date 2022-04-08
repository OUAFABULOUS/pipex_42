/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:15:41 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/08 15:40:18 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_B_H
# define PIPEX_B_H

# include "get_next_line_b.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# define STDIN 0
# define STDOUT 1
# define BUFF 1024

typedef struct s_pipex {
	int		hd;
	int		fd_in;
	int		fd_out;
	int		**fd;
	int		cmd_num;
	char	***cmdnargs;
	char	**cmdn;
	char	**paths;
	char	**cmdn_path;
}				t_pipex;

char	**ft_split(char *str, char *charset);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_strncmp(char *str1, char *str2, int n);
void	get_paths(t_pipex *p, char **env);
char	*ft_concat(char *str1, char c, char *str2);
void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path);
void	get_cmds_path(t_pipex *p);
void	handle_error(char *str);
void	init(t_pipex *p, char **av, int ac, char **env);
void	free_split(char **str);
void	free_init(t_pipex *p);
void	ft_child(t_pipex *p, char **env, int i);
void	ft_fork(t_pipex *p, char **env);
void	init_hd(t_pipex *p, char **av, int ac, char **env);
void	free_fds(t_pipex *p, int i);
void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path);
void	get_cmds_path(t_pipex *p);
void	handle_error(char *str);
void	get_cmdnargs(t_pipex *p, char **av, int hd);
void	fail(t_pipex *p, char c);
void	handle_hd(char **ret, char *limiter, int fd);

#endif
