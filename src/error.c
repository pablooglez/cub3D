/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:19:25 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/30 16:34:59 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_print_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
}

void	ft_error(t_cub *game, int use, const char *msg)
{
	ft_print_error(msg);

	if (!use)
	{
		ft_print_error("Usage: ./cub3d Maps/map.cub");
		return;
	}
	free_game(game);
	exit(EXIT_FAILURE);
}

