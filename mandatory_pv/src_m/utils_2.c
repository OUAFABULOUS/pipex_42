/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/10 07:38:54 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/pipex_m.h"

void	get_cmd_path(t_pipex *p, char *cmd, char **cmd_path)
{
	char	*full_path;
	int		i;

	i = 0;
	*cmd_path = NULL;
	while (p->paths && (p->paths)[i])
	{
		if (cmd[0] == '.' || cmd[0] == '/')
			full_path = ft_strdup(cmd);
		else
			full_path = ft_concat((p->paths)[i], '/', cmd);
		if (!access(full_path, F_OK))
		{
			*cmd_path = full_path;
			if (p->cmd1nargs == NULL)
			{
				free_init(p);
				exit (0);
			}
			return ;
		}
		free(full_path);
		i++;
	}
	handle_error("Pipex: command not found: ");
	handle_error(cmd);
	write(1, "\n", 1);
	if (p->paths && !ft_strncmp(cmd, p->cmd1, ft_strlen(p->cmd1)))
	{
		free_split(p->cmd1nargs);
		p->cmd1nargs = NULL;
	}
	else if (p->paths && !ft_strncmp(cmd, p->cmd2, ft_strlen(p->cmd2)))
	{
		free_init(p);
		exit (0);
	}
	//	if (!ft_strncmp(cmd, p->cmd2, ft_strlen(p->cmd2)))
	//	{	
	//		free_init(p);
	//		exit (1);
	//	}
}

void	get_cmds_path(t_pipex *p)
{
	if (!p->paths && p->cmd1 && ((p->cmd1)[0] != '/' || (p->cmd1)[0] != '.'))
	{
		handle_error("Pipex: command not found: ");
		handle_error(p->cmd1);
		write(1, "\n", 1);
		free_split(p->cmd1nargs);
		p->cmd1nargs = NULL;
	}
	if (!p->paths && ((p->cmd1 && (p->cmd1[0] == '/' || p->cmd1[0] == '.')) || (p->cmd2 && (p->cmd2[0] == '/'|| p->cmd2[0] == '.'))))
	{
		p->paths = malloc(1);
		p->paths[0] = "\0";
		if (p->cmd1[0] == '/' || p->cmd1[0] == '.')
		{
			get_cmd_path(p, p->cmd1, &(p->cmd1_path));
			free_split(p->cmd1nargs);
			p->cmd1nargs = NULL;
		}
		if (p->cmd2[0] == '/' || p->cmd2[0] == '.')
		{
			get_cmd_path(p, p->cmd2, &(p->cmd2_path));
			printf("I'm going to free that righ now\n");
			free_split(p->cmd2nargs);
			free_init(p);
			exit (1);
		}
	}
	if (p->paths && p->cmd1)
		get_cmd_path(p, p->cmd1, &(p->cmd1_path));
	if (!p->paths && p->cmd1 && ((p->cmd1)[0] != '/'|| (p->cmd1)[0] != '.'))
	{
		handle_error("Pipex: command not found: ");
		handle_error(p->cmd1);
		write(1, "\n", 1);
		free_split(p->cmd1nargs);
	}
	if (p->paths && p->cmd2)
		get_cmd_path(p, p->cmd2, &(p->cmd2_path));
	if (!p->paths && p->cmd2 && (p->cmd2)[0] != '/')
	{
		handle_error("Pipex: command not found: ");
		handle_error(p->cmd2);
		write(1, "\n", 1);
		free_init(p);
		exit (1);
	}
}

void	handle_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

void	init_0(t_pipex *p)
{
	p->cmd1nargs = NULL;
	p->cmd2nargs = NULL;
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->paths = NULL;
	p->cmd1_path = NULL;
	p->cmd2_path = NULL;
}

void	init(t_pipex *p, char **av, char **env)
{
	init_0(p);
	if (pipe(p->fd) == -1)
	{
		handle_error("Pipe failed.\n");
		exit(0);
	}
	p->cmd1nargs = ft_split(av[2], " ");
	p->cmd2nargs = ft_split(av[3], " ");
	p->fd_in = open(av[1], O_RDONLY);
	p->fd_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0)
		handle_error("Error while opening the infile.\n");
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
	if (p->cmd1nargs)
		p->cmd1 = p->cmd1nargs[0];
	if (p->cmd2nargs)
		p->cmd2 = p->cmd2nargs[0];
	get_paths(p, env);
	get_cmds_path(p);
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
		if (str[i])
			free(str[i]);
		free(str);
	}
	str = NULL;
}
