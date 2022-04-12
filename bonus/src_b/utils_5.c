/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:24:49 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 14:25:13 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

void	handle_hd(char **ret, char *limiter, int fd)
{
	*ret = get_next_line(STDIN, 0);
	while (1)
	{
		if (!ft_strncmp(*ret, limiter, ft_strlen(limiter)))
		{
			free(*ret);
			get_next_line(STDIN, 2);
			break ;
		}
		write(fd, *ret, ft_strlen(*ret));
		write(1, "here doc:", 9);
		free(*ret);
		*ret = get_next_line(STDIN, 0);
	}
	close(fd);
}

void	free_init(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_num)
	{
		free_split((p->cmdnargs)[i]);
		free((p->cmdn_path)[i]);
		free((p->cmdn)[i]);
		i++;
	}
	i = 0;
	while (i < p->cmd_num - 1)
	{
		free((p->fd)[i]);
		i++;
	}
	free(p->cmdnargs);
	free(p->fd);
	free(p->cmdn);
	free(p->cmdn_path);
	free_split(p->paths);
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

void	free_fds(t_pipex *p, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free((p->fd)[j]);
		j++;
	}
	free(p->fd);
}

void	get_cmdnargs(t_pipex *p, char **av, int hd)
{
	int	i;

	i = 0;
	p->cmdnargs = malloc((p->cmd_num + 1) * sizeof(char **));
	while (i < p->cmd_num)
	{
		if (hd)
			(p->cmdnargs)[i] = ft_split(av[3 + i], " ");
		else
			(p->cmdnargs)[i] = ft_split(av[2 + i], " ");
		i++;
	}
	p->cmdnargs[i] = NULL;
}
