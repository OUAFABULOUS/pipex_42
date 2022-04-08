/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/08 15:14:18 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

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
	handle_error("Pipex: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);
}

void	get_cmds_path(t_pipex *p)
{
	int	i;

	i = 0;
	p->cmdn_path = malloc((p->cmd_num + 1) * sizeof(char *));
	while (i < p->cmd_num)
	{
		get_cmd_path(p, (p->cmdn)[i], &((p->cmdn_path)[i]));
		i++;
	}
	(p->cmdn_path)[i] = NULL;
}

void	handle_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
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
