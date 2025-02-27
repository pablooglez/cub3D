/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:53:57 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/27 16:45:53 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_move_forward_back(t_cub *game, double dir)
{
	double	x;
	double	y;

	if (game->keys.w || game->keys.s)
	{
		if (game->keys.s)
			dir = -1;
		x = game->player->x + cos(game->player->view)
			* game->player->move_speed * dir;
		y = game->player->y + sin(game->player->view)
			* game->player->move_speed * dir;
		if (game->map[(int)y][(int)x] != '1'
				&& game->map[(int)(y + 0.1)][(int)x] != '1'
				&& game->map[(int)(y - 0.1)][(int)(x - 0.1)] != '1'
				&& game->map[(int)y][(int)(x + 0.1)] != '1'
				&& game->map[(int)(y + 0.1)][(int)(x + 0.1)] != '1'
				&& game->map[(int)(y - 0.1)][(int)x] != '1'
				&& game->map[(int)y][(int)(x - 0.1)] != '1'
				&& game->map[(int)(y - 0.1)][(int)(x - 0.1)] != '1')
		{
			game->player->x = x;
			game->player->y = y;
		}
	}
}

static void	ft_move_lateral(t_cub *game)
{
	double	x;
	double	y;
	double	angle;

	if (game->keys.a || game->keys.d)
	{
		angle = game->player->view;
		if (game->keys.a)
			angle = angle - M_PI_2;
		else
			angle = angle + M_PI_2;
		x = game->player->x + cos(angle) * (game->player->move_speed);
		y = game->player->y + sin(angle) * (game->player->move_speed);
		if (game->map[(int)y][(int)x] != '1')
		{
			game->player->x = x;
			game->player->y = y;
		}
	}
}

static void	ft_rotate_view(t_cub *game)
{
	if (game->keys.left)
		game->player->view -= game->player->rot_speed;
	if (game->keys.right)
		game->player->view += game->player->rot_speed;
}

void	ft_process_movement(void *param)
{
	t_cub	*game;
	double	dir;

	dir = 1;
	game = (t_cub *)param;
	ft_move_forward_back(game, dir);
	ft_move_lateral(game);
	ft_rotate_view(game);
}

void	ft_keymoves(mlx_key_data_t keydata, void *param)
{
	t_cub	*game;
	int		pressed;

	game = (t_cub *) param;
	pressed = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->init);
	else if (keydata.key == MLX_KEY_W)
		game->keys.w = pressed;
	else if (keydata.key == MLX_KEY_S)
		game->keys.s = pressed;
	else if (keydata.key == MLX_KEY_A)
		game->keys.a = pressed;
	else if (keydata.key == MLX_KEY_D)
		game->keys.d = pressed;
	else if (keydata.key == MLX_KEY_LEFT)
		game->keys.left = pressed;
	else if (keydata.key == MLX_KEY_RIGHT)
		game->keys.right = pressed;
}
