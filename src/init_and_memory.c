/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:31 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/26 18:39:05 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_game(t_cub *game)
{
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		ft_error(game, 1, "Malloc failed");
	game->player->x = WIN_WIDTH / 2;
	game->player->y = WIN_HEIGHT / 2;
	game->player->view = M_PI / 2;
	game->player->move_speed = 0.12;
	game->player->rot_speed = 0.12;
	game->keys = (t_keys){0};
	game->fd = -1;
}

void	init_image(t_cub *game)
{
	mlx_delete_image(game->init, game->img_window);
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->init, game->img_window, 0, 0);
}

void	init_wall_data(t_wall_data *wall, t_cub *game, int x)
{
	double	perp_dist;

	perp_dist = game->rays[x].perpection_distance;
	wall->height = (int)(WIN_HEIGHT / (perp_dist * 1.5));
	wall->start = (WIN_HEIGHT - wall->height) / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = (WIN_HEIGHT + wall->height) / 2;
	if (wall->end > WIN_HEIGHT)
		wall->end = WIN_HEIGHT;
	wall->x = x;
}

t_texture_data	init_texture_data(t_cub *game, t_wall_data wall)
{
	t_texture_data	data;

	data.ray = &game->rays[wall.x];
	data.texture = ft_select_texture(game, data.ray->side);
	if (!data.texture || !data.texture->pixels)
	{
		data.tex_x = 0;
		data.step = 0;
		data.tex_pos = 0;
		return (data);
	}
	data.tex_x = ft_get_texture_x(data.ray, data.texture);
	data.step = (double)data.texture->height / wall.height;
	data.tex_pos = (wall.start - WIN_HEIGHT / 2.0 + wall.height / 2.0)
		* data.step;
	return (data);
}
