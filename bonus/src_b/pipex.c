/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 02:21:18 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_b/pipex_b.h"
#include <stdio.h>
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
		printf("%d\n", *(&p)->err_null_cmd);
		if (!(&p)->err_null_cmd && !(&p)->err_cmd_nf)
		{
			printf("Oups entered here while I shouldn't have\n");
			ft_fork(&p, env);
		}
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (0);
}
