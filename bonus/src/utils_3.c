/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:19:14 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 09:26:33 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_init(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_num)
	{
			free_split((p->cmdnargs)[i]);
			free((p->fd)[i]);
			free((p->cmdn)[i]);
			free((p->cmdn_path)[i]);
			i++;
	}	
	free(p->cmdnargs);
	free(p->fd);
	free(p->cmdn);
	free(p->cmdn_path);
	free_split(p->paths);
}

void	ft_child(t_pipex *p, char **env)
{
	close(p->fd[0]);
	dup2(p->fd[1], STDOUT);
	close(p->fd[1]);
	dup2(p->fd_in, STDIN);
	close(p->fd_in);
	close(p->fd_out);
	execve(p->cmd1_path, p->cmd1_args, env);
	exit(0);
}

void	ft_parent(t_pipex *p, char **env)
{
	close(p->fd_in);
	close(p->fd[1]);
	dup2(p->fd[0], STDIN);
	close(p->fd[0]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
//	close(p->fd);
	wait(NULL);
	execve(p->cmd2_path, p->cmd2_args, env);
}
/*
void	ft_child_2(t_pipex *p, char **env)
{
	close(p->fd[1]);
	dup2(p->fd[0], STDIN);
	close(p->fd[0]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	execve(p->cmd2_path, p->cmd2_args, env);
	exit(0);
}
*/
void	ft_fork(t_pipex *p, char **env)
{
	int	pid1;
//	int	pid2;
//	int status;

	pid1 = fork();
	if (pid1 == -1)
	{
		handle_error("Fork failed.\n");
		free_init(p);
		exit(0);
	}
	if (pid1 == 0)
		ft_child(p, env);
	ft_parent(p, env);
/*	pid2 = fork();
	if (pid2 == -1)
	{
		handle_error("Fork failed.\n");
		free_init(p);
		exit(0);
	}
	if (pid2 == 0)
		ft_child_2(p, env);
	close (p->fd[0]);
	close (p->fd[1]);
//	close (p->fd_in);
//	close (p->fd_in);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
*/
	}
