/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:55:18 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 02:55:08 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"
#include <stdio.h>

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

void	init_hd(t_pipex *p, char **av, int ac, char **env)
{
	char	*ret;
	int		file;

	p->hd = 1;
	init_p1(p, av, ac, env);
	file = open (".heredoc_omo_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(1, "here doc:", 9);
	handle_hd(&ret, av[2], file);
	p->fd_in = open(".heredoc_omo_tmp", O_RDONLY);
	if (p->fd_in < 0)
	{
		unlink(".heredoc_omo_tmp");
		handle_error("Error while opening the temporary infile.\n");
	}
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
//	int	i;
//	i = 0;
//	printf("%d\n",p->cmd_num);
//	while (i < p->cmd_num)
//	{
//		printf("%s\n", p->cmdnargs[i][0]);
//		i++;
//	}
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
