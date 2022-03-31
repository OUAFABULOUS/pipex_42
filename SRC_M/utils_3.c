/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:19:14 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 22:06:35 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_m.h"

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

void	free_init(t_pipex *p)
{
	free_split(p->cmd1nargs);
	free_split(p->cmd2nargs);
	free_split(p->paths);
	free(p->cmd1_path);
	free(p->cmd2_path);
}

void	ft_child_1(t_pipex *p, char **env)
{
	close(p->fd[0]);
	dup2(p->fd[1], STDOUT);
	close(p->fd[1]);
	dup2(p->fd_in, STDIN);
	close(p->fd_in);
	close(p->fd_out);
//	if (execve(p->cmd1_path, p->cmd1nargs, env) == -1)
	execve(p->cmd1_path, p->cmd1nargs, env);
//		fail(p, 'e');
	exit(0);
}

void	ft_child_2(t_pipex *p, char **env)
{
	close(p->fd_in);
	close(p->fd[1]);
	dup2(p->fd[0], STDIN);
	close(p->fd[0]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	execve(p->cmd2_path, p->cmd2nargs, env);
//		fail(p, 'e');
	exit(0);
}

void	ft_fork(t_pipex *p, char **env)
{
	int	pid1;
	int	pid2;
	int	status;

	pid1 = fork();
	if (pid1 == -1)
		fail(p, 'p');
	if (pid1 == 0)
		ft_child_1(p, env);
	pid2 = fork();
	if (pid2 == -1)
		fail(p, 'p');
	if (pid2 == 0)
		ft_child_2(p, env);
	close (p->fd[0]);
	close (p->fd[1]);
	close (p->fd_in);
	close (p->fd_out);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
