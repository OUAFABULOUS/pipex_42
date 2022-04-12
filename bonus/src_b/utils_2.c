/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 02:51:23 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"
#include <stdio.h>
void	no_path(t_pipex *p, char *cmd, char **cmd_path, char **full_path)
{
	if (cmd[0] && (cmd[0] == '.' || cmd[0] == '/'))
	{
		*full_path = ft_strdup(cmd);
		if (!access(*full_path, F_OK))
		{
			*cmd_path = *full_path;
			return ;
		}
		free(full_path);
	}
	p->err_cmd_nf = 1;
	handle_error("Pipex: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);

}

void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path, int i)
{
	char	*full_path;
	int		j;

	p->rep_1_exe = 0;
	p->rep_n_exe = 0;
	*p->err_null_cmd = 0;
	p->err_cmd_nf = 0;
	j = 0;
	*cmd_path = NULL;
	if (cmd && !p->paths)
	{
		no_path(p, cmd, cmd_path, &full_path);
		return ;
	}
	while (cmd && p->paths && (p->paths)[j])
	{
		if (cmd[0] && (cmd[0] == '.' || cmd[0] == '/'))
			full_path = ft_strdup(cmd);
		else
			full_path = ft_concat((p->paths)[j], '/', cmd);
		if (!access(full_path, F_OK))
		{
			*cmd_path = full_path;
			return ;
		}
		free(full_path);
		j++;
	}
	if (cmd)
		p->err_cmd_nf = 1;
	if (!cmd)
	{
		printf("I entered here\n");
		if (i != 0 && i != p->cmd_num -1) 
		{
			printf("I entered here2\n");
			*p->err_null_cmd = 1;
			printf("This is what I became: %d\n", *p->err_null_cmd);
		}
		if (i == 0)
		{
			p->rep_1_exe = 1;
			return ;
		}
		if (i == p->cmd_num -1)
		{
			p->rep_n_exe = 1;
			return ;
		}
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
		printf("%d\n", i);
		if (p->cmdn[i])
			printf("%s\n", p->cmdn[i]);
		get_cmd_path(p, (p->cmdn)[i], &((p->cmdn_path)[i]), i);
		i++;
	}
	(p->cmdn_path)[i] = NULL;
}

void	handle_error(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
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

void	fill_with_cat(char *str, t_pipex *p, int n)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (!n)
			(p->cmdnargs)[0][0][i] = str[i];
		if (n)
			(p->cmdnargs)[p->cmd_num - 1][0][i] = str[i];
		i++;
	}
		if (!n)
			(p->cmdnargs)[0][0][i] = '\0';
		if (n)
			(p->cmdnargs)[p->cmd_num - 1][0][i] = '\0';
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
	if (!(*((p->cmdnargs)[0])) || !(*((p->cmdnargs)[p->cmd_num - 1])))
	{
		if (!(*((p->cmdnargs)[0])))
		{
			free((p->cmdnargs)[0]);
			p->cmdnargs[0] = malloc (1 * sizeof(char *));
			p->cmdnargs[0][0] = malloc(13);
			fill_with_cat("/usr/bin/cat", p, 0);
		}
		if (!(*((p->cmdnargs)[p->cmd_num - 1])))
		{
			free(*((p->cmdnargs)[p->cmd_num - 1]));
			free((p->cmdnargs)[p->cmd_num - 1]);
			p->cmdnargs[p->cmd_num - 1] = malloc (2 * sizeof(char *));
			p->cmdnargs[p->cmd_num - 1][0] = malloc(13);
			p->cmdnargs[p->cmd_num - 1][1] = '\0';
			fill_with_cat("/usr/bin/cat", p, 1);
		}
	}
	p->cmdnargs[i] = NULL;
}
