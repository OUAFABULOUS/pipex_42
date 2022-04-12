/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:43:21 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 15:30:10 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_b/get_next_line_b.h"

int	sub_gnl(int *r_read, int fd, char (*buff)[BUFFER_SIZE + 1], char **b_buff)
{
	while (get_index(*b_buff, '\n') == -1)
	{
		*r_read = read(fd, *buff, BUFFER_SIZE);
		if (*r_read < 0)
			return (0);
		(*buff)[*r_read] = '\0';
		if (*r_read > 0)
		{
			if (!*b_buff)
				*b_buff = ft_strndup(*buff, get_index(*buff, '\0'));
			else
				*b_buff = ft_strjoin(*b_buff, *buff);
		}
		else
			break ;
	}
	return (1);
}

char	*get_next_line(int fd, int ind)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*b_buff;
	int			r_read;

	if (fd < 0)
		return (NULL);
	if (ind == 2)
	{
		free(b_buff);
		return (NULL);
	}
	*buff = '\0';
	if (!sub_gnl(&r_read, fd, &buff, &b_buff))
		return (NULL);
	return (b_buff_to_line(&b_buff));
}
