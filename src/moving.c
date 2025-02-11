/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:53:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/11 18:08:26 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_keymoves(mlx_key_data_t keydata, void *param)
{
	t_cub	*game;

	game = (t_cub *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->init);
	//ft_keymoves_w(keydata, param);
	//ft_keymoves_a(keydata, param);
	//ft_keymoves_s(keydata, param);
	//ft_keymoves_d(keydata, param);
}
