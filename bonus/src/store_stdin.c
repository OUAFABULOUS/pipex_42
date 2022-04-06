/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:55:05 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 11:25:57 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

int	count_chars_stdin(void)
{
	int		count;
	char	c;

	while (read(0, &c, 1))
			count++;
}

int	main()
{
	printf("%d\n", count_chars_stdin());
	return (0);
}
