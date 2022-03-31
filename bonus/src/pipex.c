/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 10:44:42 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;

	if (argc >= 5)
	{
		if (!ft_strncmp(argv[1], "here_doc", 8))
			init_hd(&p, argv, argc, env);
		else
			init(&p, argv, argc, env);
		ft_fork(&p, env);
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (0);
}
