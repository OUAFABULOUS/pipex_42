/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_m.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:15:41 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/01 18:45:23 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_M_H
# define PIPEX_M_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

# define STDIN 0
# define STDOUT 1

typedef struct s_pipex {
	int		fd_in;
	int		fd_out;
	int		fd[2];
	char	**cmd1nargs;
	char	**cmd2nargs;
	char	*cmd1;
	char	*cmd2;
	char	**paths;
	char	*cmd1_path;
	char	*cmd2_path;
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
void	init(t_pipex *p, char **av, char **env);
void	free_split(char **str);
void	free_init(t_pipex *p);
void	ft_child(t_pipex *p, char **env);
void	ft_parent(t_pipex *p, char **env);
void	ft_fork(t_pipex *p, char **env, int *ret);

#endif
