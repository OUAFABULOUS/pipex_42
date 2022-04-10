/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/10 19:17:05 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;

	//You gotta change that for mandatory
	if (argc >= 5)
	{
		if (!ft_strncmp(argv[1], "here_doc", 8))
			init_hd(&p, argv, argc, env);
		else
			init(&p, argv, argc, env);
		if (!(&p)->err_null_cmd && !(&p)->err_null_cmd)
			ft_fork(&p, env);
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (0);
}
