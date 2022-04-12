/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:55:18 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 15:38:48 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/pipex_m.h"

void	get_cmds(t_pipex *p)
{
	int	i;

	i = 0;
	p->cmdn = malloc((p->cmd_num + 1) * sizeof(char *));
	while (i < p->cmd_num)
	{
		if (!*((p->cmdnargs)[i]))
			(p->cmdn)[i] = NULL;
		else
			(p->cmdn)[i] = ft_strdup((p->cmdnargs)[i][0]);
		i++;
	}
	(p->cmdn)[i] = NULL;
}

void	init_p1(t_pipex *p, char **av, int ac, char **env)
{
	int	i;

	*(p->err_null_cmd) = 0;
	*(p->err_cmd_nf) = 0;
	p->paths = NULL;
	i = -1;
	if (p->hd)
	{
		p->cmd_num = ac - 4;
		get_cmdnargs(p, av, 1);
	}
	p->fd_out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
	get_cmds(p);
	p->fd = malloc((p->cmd_num -1) * sizeof(int *));
	while (++i < p->cmd_num -1)
	{
		(p->fd)[i] = malloc(2 * sizeof(int));
		if (pipe((p->fd)[i]) == -1)
			fail(p, 'p');
	}
	get_paths(p, env);
	get_cmds_path(p);
}

void	init_0(t_pipex *p)
{
	int	i;

	i = 0;
		p->cmdnargs = malloc((p->cmd_num + 1) * sizeof(char *));
		p->cmdn = NULL;
		p->cmdn_path[i] = NULL;
	while (i < p->cmd_num)
	{
		p->cmdnargs[i] = NULL;
		p->cmdn[i] = NULL;
		p->cmdn_path[i] = NULL;
		i++;
	}
	p->fd = NULL;
	p->paths = NULL;
}

void	init(t_pipex *p, char **av, int ac, char **env)
{
	p->hd = 0;
	p->cmd_num = ac - 3;
	get_cmdnargs(p, av, 0);
	init_p1(p, av, ac, env);
	p->fd_in = open(av[1], O_RDONLY);
	if (p->fd_in < 0)
		handle_error("Error while opening the infile.\n");
}
