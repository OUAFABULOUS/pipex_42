/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:45:28 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 10:18:26 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int	get_index(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(char *str, int len)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = malloc(len +1);
	if (!ret)
		return (NULL);
	while (i < len && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*ret;
	int		i;
	int		j;

	if (!str1 && !str2)
		return (NULL);
	if (!str1 || !str2)
		ret = malloc(sizeof(char)
				* (get_index(str1, '\0') + get_index(str2, '\0') + 2));
	else
		ret = malloc(sizeof(char)
				* (get_index(str1, '\0') + get_index(str2, '\0') + 1));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		ret[i] = str1[i];
	while (str2[++j])
		ret[i + j] = str2[j];
	ret[i + j] = '\0';
	free(str1);
	return (ret);
}

char	*b_buff_to_line(char **b_buff)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (get_index(*b_buff, '\n') > -1)
	{
		line = ft_strndup(*b_buff, get_index(*b_buff, '\n') + 1);
		tmp = ft_strndup(&(*b_buff)[get_index(*b_buff, '\n') + 1],
				get_index(*b_buff, '\0'));
		free(*b_buff);
		*b_buff = tmp;
		return (line);
	}
	else if (*b_buff)
	{
		if (*b_buff[0])
			line = ft_strndup(*b_buff, get_index(*b_buff, '\0'));
		free(*b_buff);
		*b_buff = NULL;
	}
	if (line)
		return (line);
	else
		return (NULL);
}
