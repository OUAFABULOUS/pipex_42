/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/04/12 15:39:16 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/pipex_m.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;

	if (argc == 5)
	{
		init(&p, argv, argc, env);
		if (!*((&p)->err_null_cmd) && !*((&p)->err_cmd_nf))
			ft_fork(&p, env);
		free_init(&p);
	}
	else
		handle_error("Please respect the syntax!\n");
	return (0);
}
