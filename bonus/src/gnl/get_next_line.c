/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:43:21 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 10:18:29 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*b_buff;
	int			r_read;

	if (fd < 0)
		return (NULL);
	*buff = '\0';
	while (get_index(b_buff, '\n') == -1)
	{
		r_read = read(fd, buff, BUFFER_SIZE);
		if (r_read < 0)
			return (NULL);
		buff[r_read] = '\0';
		if (r_read > 0)
		{
			if (!b_buff)
				b_buff = ft_strndup(buff, get_index(buff, '\0'));
			else
				b_buff = ft_strjoin(b_buff, buff);
		}
		else
			break ;
	}
	return (b_buff_to_line(&b_buff));
}
