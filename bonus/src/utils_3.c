/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:19:14 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/07 16:09:43 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
/*
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
*/
void	close_all_fds(t_pipex *p)
{
	int	i;

	i = 0;
	close(p->fd_in);
	close(p->fd_out);
	while (i < p->cmd_num - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
}

void	ft_child(t_pipex *p, char **env, int i)
{
	if (i != 0)
		dup2(p->fd[i - 1][0], STDIN);
	if (!i)
		dup2(p->fd_in, STDIN);
	if (i != p->cmd_num - 1)
		dup2(p->fd[i][1], STDOUT);
	if (i == p->cmd_num - 1)
		dup2(p->fd_out, STDOUT);
	close_all_fds(p);
	execve(p->cmdn_path[i], p->cmdnargs[i], env);
	exit(0);
}
/*
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
	int	*pid;
	int	i;
	int status;

	pid = malloc((p->cmd_num) *  sizeof(int));
	i = 0;
	while (i < p->cmd_num)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			handle_error("Fork failed.\n");
			free_init(p);
			exit(0);
		}
		if (!pid[i])
			ft_child(p, env, i);
		i++;
	}
	close_all_fds(p);
	while (i < p->cmd_num)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (pid)
		free (pid);
}
