/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:19:25 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/26 21:30:56 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_print_error(const char *msg)
{
	ft_putstr_fd("Error \n", 2);
	ft_putendl_fd(msg, 2);
}

void	ft_error(t_cub *game, int use, const char *msg)
{
	ft_print_error(msg);
	if (!use)
		return ;
	free_game(game);
	exit(EXIT_FAILURE);
}
