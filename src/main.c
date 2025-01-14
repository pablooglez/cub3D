/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:17:11 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/14 21:38:57 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	//t_cub	*game;

	if (argc == 2)
	{
		//ft_check_game(&game, argv[1]);
		//ft_mlx_init(&game);
		//ft_cleanup(&game);
	}
	else
		ft_error("ERROR: Invalid number of arguments");
	return (0);
}
