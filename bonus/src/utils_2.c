/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:18:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/07 17:02:26 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>
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

void	double_ptr_print(char **str)
{
	int	i;

	i = 0;
	printf("\n");
	while(str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

void	triple_ptr_print(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		double_ptr_print(str[i]);
		i++;
	}
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

void	get_cmds(t_pipex *p)
{
	int	i;

	i = 0;
	p->cmdn = malloc((p->cmd_num + 1) * sizeof(char *)); 
	while (i < p->cmd_num)
	{
		(p->cmdn)[i] = ft_strdup((p->cmdnargs)[i][0]);
		i++;
	}
	(p->cmdn)[i] = NULL;
}

void	init_hd(t_pipex *p, char **av, int ac, char **env)
{
	int		i;
	char	*ret;
	int		file;

	i = 0;
	p->cmd_num = ac - 4;
	printf("Number of commands: %d\n", p->cmd_num);
	p->fd = malloc((p->cmd_num -1) * sizeof(int *));
	while (i < p->cmd_num -1)
	{
		(p->fd)[i] = malloc(2 * sizeof(int));
		if (pipe((p->fd)[i]) == -1)
		{
			handle_error("Pipe failed.\n");
			free_fds(p, i);
			exit(0);
		}
	i++;
	}
	p->fd_out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	file = open (".heredoc_omo_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
	get_cmdnargs(p, av, 1);
	get_cmds(p);
	write(1, "here doc:", 9);
	ret = get_next_line(STDIN);
	while (ret)
	{
		if (!ft_strncmp(ret, av[2], ft_strlen(av[2])))
			break ;
		write(file, ret, ft_strlen(ret));
		write(1, "here doc:", 9);
		free(ret);
		ret = get_next_line(STDIN);
	}
	if (ret)
		free(ret);
	close(file);
	p->fd_in = open(".heredoc_omo_tmp", O_RDONLY);
	if (p->fd_in < 0)
	{
		unlink(".heredoc_omo_tmp");
		handle_error("Error while opening the temporary infile.\n");
	}
	get_paths(p, env);
	get_cmds_path(p);

//	p->fd_in = open(".tmpp", O_RDONLY);
/*
	close(pipe_test[1]);
	else
	{
	while (read(pipe_test[0], &c, 1))
	{
	printf("%c", c);
	write(p->fd_in, &c, 1);
	}
	write(p->fd_in, "\0", 1);
	}
	close(pipe_test[0]);
	close(p->fd_in);
	*/
/*
	printf("le nombre de caracteres dans ton fichier tmp est: %d\n", count);
	*/
/*
	int		i;

	i = 0;
	p->cmd_num = ac - 4;
//	printf("Number of commands: %d\n", p->cmd_num);
	p->fd = malloc((p->cmd_num -1) * sizeof(int *));
	get_cmdnargs(p, av, 1);
	triple_ptr_print(p->cmdnargs);
	get_cmds(p);
	double_ptr_print(p->cmdn);
	p->fd_in = open(av[1], O_RDWR | O_CREAT, 0644);
	dup2(p->fd_in, STDIN);
	close(p->fd_in);
	p->fd_out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0)
		handle_error("Error while opening the infile.\n");
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
	get_paths(p, env);
*/
	}


void	init(t_pipex *p, char **av, int ac, char **env)
{
	int	i;

	i = 0;
	p->cmd_num = ac - 3;
	p->fd = malloc((p->cmd_num -1) * sizeof(int *));
	while (i < p->cmd_num - 1)
	{
		(p->fd)[i] = malloc(2 * sizeof(int));
		if (pipe((p->fd)[i]) == -1)
		{
			handle_error("Pipe failed.\n");
			free_fds(p, i);
			exit(0);
		}
	i++;
	}
	get_cmdnargs(p, av, 0);
	get_cmds(p);
	p->fd_in = open(av[1], O_RDONLY);
	p->fd_out = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p->fd_in < 0)
		handle_error("Error while opening the infile.\n");
	if (p->fd_out < 0)
		handle_error("Error while opening the outfile.\n");
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
		free(str[i]);
		free(str);
	}
	str = NULL;
}

void	free_init(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_num + 1)
	{
			free_split((p->cmdnargs)[i]);
			free((p->cmdn_path)[i]);
			free((p->cmdn)[i]);
			i++;
	}
	i = 0;
	while ( i < p->cmd_num - 1)
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

