/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:53:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/19 10:29:21 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_move_ws(t_cub *game, int key)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (key == MLX_KEY_W)
	{
		new_x += cos(game->player->view) * game->player->move_speed;
		new_y += sin(game->player->view) * game->player->move_speed;
	}
	else if (key == MLX_KEY_S)
	{
		new_x -= cos(game->player->view) * game->player->move_speed;
		new_y -= sin(game->player->view) * game->player->move_speed;
	}
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
}

void	ft_rotate_ad(t_cub *game, int key)
{
	if (key == MLX_KEY_A)
		game->player->view -= game->player->rot_speed;
	else if (key == MLX_KEY_D)
		game->player->view += game->player->rot_speed;
}

void	ft_process_movement(void *param)
{
	t_cub	*game;
	double	new_x;
	double	new_y;

	game = (t_cub *)param;
	new_x = game->player->x;
	new_y = game->player->y;
	if (game->keys[MLX_KEY_W])
	{
		new_x += cos(game->player->view) * game->player->move_speed;
		new_y += sin(game->player->view) * game->player->move_speed;
	}
	if (game->keys[MLX_KEY_S])
	{
		new_x -= cos(game->player->view) * game->player->move_speed;
		new_y -= sin(game->player->view) * game->player->move_speed;
	}
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	if (game->keys[MLX_KEY_A])
		game->player->view -= game->player->rot_speed;
	if (game->keys[MLX_KEY_D])
		game->player->view += game->player->rot_speed;
}

void	ft_keymoves(mlx_key_data_t keydata, void *param)
{
	t_cub	*game;

	game = (t_cub *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->init);
	else if (keydata.action < 256)
	{
		if (keydata.action == MLX_PRESS)
			game->keys[keydata.key] = 1;
		else if (keydata.action == MLX_RELEASE)
			game->keys[keydata.key] = 0;
	}
}
