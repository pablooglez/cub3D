/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:36:08 by albelope          #+#    #+#             */
/*   Updated: 2025/02/23 12:53:47 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*ft_select_texture(t_cub *game, int side)
{
	if (side == NORTH)
		return (game->coor.txt_north_i);
	if (side == SOUTH)
		return (game->coor.txt_south_i);
	if (side == WEST)
		return (game->coor.txt_west_i);
	return (game->coor.txt_east_i);
}

int	ft_get_texture_x(t_ray *ray, mlx_texture_t *texture)
{
	float	hit_pos;
	int		tex_x;

	if (ray->side == EAST || ray->side == WEST)
		hit_pos = ray->hit_y - floor(ray->hit_y);
	else
		hit_pos = ray->hit_x - floor(ray->hit_x);
	tex_x = (int)(hit_pos * texture->width);
	if (tex_x >= (int)texture->width)
		tex_x = (int)texture->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

static void	draw_floor_ceiling(t_cub *game, t_wall_data *wall)
{
	int	y;

	y = 0;
	while (y < wall->start)
	{
		mlx_put_pixel(game->img_window, wall->x, y,
			get_rgba(&game->coor.t_ceiling));
		y++;
	}
	y = wall->end;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(game->img_window, wall->x, y,
			get_rgba(&game->coor.t_floor));
		y++;
	}
}

static void	ft_draw_textured_wall(t_cub *game, t_wall_data wall)
{
	t_texture_data	data;
	int				y;
	int				tex_y;
	uint8_t			*pixel;

	data = init_texture_data(game, wall);
	if (!data.texture || !data.texture->pixels)
		return ;
	y = wall.start;
	while (y < wall.end)
	{
		tex_y = (int)data.tex_pos;
		if (tex_y >= (int)data.texture->height)
			tex_y = (int)data.texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		data.tex_pos += data.step;
		pixel = &data.texture->pixels[(tex_y
				* data.texture->width + data.tex_x) * 4];
		mlx_put_pixel(game->img_window, wall.x, y,
			((uint32_t)pixel[0] << 24) | ((uint32_t)pixel[1] << 16)
			| ((uint32_t)pixel[2] << 8) | 255);
		y++;
	}
}

void	put_textures(void *param)
{
	t_cub		*game;
	int			x;
	t_wall_data	wall;

	game = (t_cub *)param;
	ft_raycasting(game);
	init_image(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_wall_data(&wall, game, x);
		draw_floor_ceiling(game, &wall);
		ft_draw_textured_wall(game, wall);
		x++;
	}
}
