/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:16:15 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/10 18:15:32 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	if (!str)
		return (NULL);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] && (str1[i] == str2[i]) && n)
	{
		i++;
		n--;
	}
	if (n)
		return (str1[i] - str2[i]);
	else
		return (0);
}

void	get_paths(t_pipex *p, char **env)
{
	int		i;
	char	*path;

	p->paths = NULL;
	i = 0;
	path = NULL;
	while (env && *env && (env)[i])
	{
		if (!ft_strncmp((env)[i], "PATH=", 5))
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (path)
	{
		p->paths = ft_split(path, ":");
		free(path);
	}
}

char	*ft_concat(char *str1, char c, char *str2)
{
	int		len1;
	int		len2;
	char	*res;
	int		i;
	int		j;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = malloc(len1 + len2 + 2);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len1)
		res[i] = str1[i];
	res[i] = c;
	i++;
	j = -1;
	while (++j < len2)
		res[i + j] = str2[j];
	res[i + j] = 0;
	return (res);
}
