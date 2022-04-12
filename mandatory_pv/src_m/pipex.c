/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/10 07:31:11 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/pipex_m.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;
	int		ret;

	if (argc == 5)
	{
		init(&p, argv, env);
		if ((&p)->cmd1nargs && (&p)->cmd2nargs)
		{
			ft_fork(&p, env, &ret);
		}	
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (ret);
}
