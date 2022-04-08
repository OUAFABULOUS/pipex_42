/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:24:49 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/08 15:38:12 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

void	handle_hd(char **ret, char *limiter, int fd)
{
	*ret = get_next_line(STDIN);
	while (*ret)
	{
		if (!ft_strncmp(*ret, limiter, ft_strlen(limiter)))
			break ;
		write(fd, *ret, ft_strlen(*ret));
		write(1, "here doc:", 9);
		free(*ret);
		*ret = get_next_line(STDIN);
	}
	if (*ret)
		free(*ret);
	close(fd);
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
