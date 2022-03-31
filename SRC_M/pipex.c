/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/03/31 18:43:57 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_m.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;

	if (argc == 5)
	{
		init(&p, argv, env);
		ft_fork(&p, env);
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (0);
}
