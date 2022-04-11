/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:19:14 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/11 18:02:08 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

void	fail(t_pipex *p, char c)
{
	if (c == 'p')
		handle_error("Pipe failed.\n");
	if (c == 'f')
		handle_error("Fork failed.\n");
	if (c == 'e')
		handle_error("Execve failed.\n");
	free_init(p);
	exit(0);
}

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
//	if ((!i && p->rep_1_exe) || (i == p->cmd_num - 1 && p->rep_n_exe))
//		execve(cat_1, cat, env);
//	else
		execve(p->cmdn_path[i], p->cmdnargs[i], env);
	exit(0);
}

void	ft_fork(t_pipex *p, char **env)
{
	int	*pid;
	int	i;
	int	status;

	pid = malloc((p->cmd_num) * sizeof(int));
	i = 0;
	while (i < p->cmd_num)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			fail(p, 'f');
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
