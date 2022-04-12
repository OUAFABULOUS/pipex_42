/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 14:26:24 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

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
	*(p->err_cmd_nf) = 1;
	handle_error("Pipex: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);
}

void	no_cmd(t_pipex *p)
{
	*(p->err_null_cmd) = 1;
	handle_error("Pipex: permission denied: ");
	write(1, "\n", 1);
	return ;
}

void	cmd_n_path(t_pipex *p, char *cmd, char **cmd_path, char **full_path)
{
	int		j;

	j = -1;
	*cmd_path = NULL;
	while (cmd && p->paths && (p->paths)[++j])
	{
		if (cmd[0] && (cmd[0] == '.' || cmd[0] == '/'))
			*full_path = ft_strdup(cmd);
		else
			*full_path = ft_concat((p->paths)[j], '/', cmd);
		if (!access(*full_path, F_OK))
		{
			*cmd_path = *full_path;
			return ;
		}
		free(*full_path);
	}
	*(p->err_cmd_nf) = 1;
	handle_error("Pipex: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);
	return ;
}

void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path)
{
	char	*full_path;

	*cmd_path = NULL;
	if (!cmd)
		no_cmd(p);
	else if (cmd && !p->paths)
		no_path(p, cmd, cmd_path, &full_path);
	else
		cmd_n_path(p, cmd, cmd_path, &full_path);
	return ;
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
