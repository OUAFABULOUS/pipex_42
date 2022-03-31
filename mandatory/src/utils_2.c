/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 03:31:04 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path)
{
	char	*full_path;
	int		i;

	i = 0;
	*cmd_path = NULL;
	while ((p->paths)[i])
	{
		if (cmd[0] == '.' || cmd[0] == '/')
			full_path = ft_strdup(cmd);
		else
			full_path = ft_concat((p->paths)[i], '/', cmd);
		if (!access(full_path, F_OK))
		{
			*cmd_path = full_path;
			return ;
		}
		free(full_path);
		i++;
	}
	handle_error("zsh: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);
}

void	get_cmds_path(t_pipex *p)
{
	get_cmd_path(p, p->cmd1, &(p->cmd1_path));
	get_cmd_path(p, p->cmd2, &(p->cmd2_path));
}

void	handle_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}
/*
void	double_ptr_print(char **str)
{
int	i;

i = 0;
printf("\n");
while(str[i])
{
	printf("%s\n", str[i]);
	i++;
}
printf("\n");
}
*/
void	init(t_pipex *p, char **av, char **env)
{
	if (pipe(p->fd) == -1)
	{
		handle_error("Pipe failed.\n");
		exit(0);
	}
	p->cmd1nargs = ft_split(av[2], " ");
	p->cmd2nargs = ft_split(av[3], " ");
	p->fd_in = open(av[1], O_RDONLY);
	p->fd_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0)
		handle_error("Error while opening the infile.\n");
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
	p->cmd1 = p->cmd1nargs[0];
//	printf("Commande 1: %s\n", p->cmd1);
	p->cmd2 = p->cmd2nargs[0];
//	printf("Commande 2: %s\n", p->cmd2);
	p->cmd1_args = p->cmd1nargs;
//	double_ptr_print(p->cmd1nargs);
	p->cmd2_args = p->cmd2nargs;
//	double_ptr_print(p->cmd2nargs);
	get_paths(p, env);
//	printf("get_paths_done\n");
	get_cmds_path(p);
//	printf("get_cmds_path_done\n");
//	printf("Path for the 1st cmd: %s\n", p->cmd1_path);
//	printf("Path for the 1st cmd: %s\n", p->cmd2_path);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{	
			free(str[i]);
			i++;
		}
		free(str[i]);
		free(str);
	}
	str = NULL;
}
