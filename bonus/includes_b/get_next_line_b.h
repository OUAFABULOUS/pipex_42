/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:51:39 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/08 15:40:37 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_B_H
# define GET_NEXT_LINE_B_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024

int		get_index(char *str, char c);
char	*ft_strndup(char *str, int len);
char	*ft_strjoin(char *str1, char *str2);
char	*b_buff_to_line(char **b_buff);
char	*get_next_line(int fd);

#endif
