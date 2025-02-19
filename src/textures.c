/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:36:08 by albelope          #+#    #+#             */
/*   Updated: 2025/02/19 13:01:39 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static unsigned int	get_rgba(t_color *color)									// Convierte una estructura t_color a un valor RGBA en formato uint32_t
{
	return ((unsigned int)color->r << 24 | (unsigned int)color->g << 16
		| (unsigned int)color->b << 8 | 255);									// El último byte es 255 (opacidad máxima)
}

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
	float		hit_pos;
	int			tex_x;

	hit_pos = 0.0;
	if (ray->side == EAST || ray->side == WEST)
		hit_pos = ray->hit_y - floor(ray->hit_y);				// floor incluida en math.h -se puede usar(double).
	else
		hit_pos = ray->hit_x - floor(ray->hit_x);
	tex_x = (int)(hit_pos * (texture->width - 1));
	return (tex_x);
}

void	ft_draw_textured_wall(t_cub *game, int x, int top, int bottom)
{
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	int				screen_y;
	uint8_t			*pixel;

	ray = &game->rays[x];
	texture = ft_select_texture(game, ray->side);
	if (!texture || !texture->pixels)
		return ;
	tex_x = ft_get_texture_x(ray, texture);
	screen_y = top;
	while (screen_y < bottom)
	{
		tex_y = ((screen_y - top) * texture->height) / (bottom - top);
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		mlx_put_pixel(game->img_window, x, screen_y, ((uint32_t)pixel[0] << 24)
			| ((uint32_t)pixel[1] << 16) | ((uint32_t)pixel[2] << 8)  | 255);
		screen_y++;
	}
}

void	ft_calculate_wall_dimensions(t_cub *game, int x, int *top, int *bottom)
{
	double	distance;
	int		wall_height;

	distance = game->rays[x].perpection_distance;
	if (distance < 0.1)
		distance = 0.1;
	if (distance > 50)
		distance = 50;
	wall_height = (int)(WIN_HEIGHT / (distance * 1.5));
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	*top = (WIN_HEIGHT - wall_height) / 2;
	if (*top < 0)
		*top = 0;
	*bottom = (WIN_HEIGHT + wall_height) / 2;
	if (*bottom > WIN_HEIGHT)
		*bottom = WIN_HEIGHT;
}

void	ft_draw_walls_and_floor(t_cub *game, int x, int top, int bottom)
{
	int	j;

	j = 0;
	while (j < top)
		mlx_put_pixel(game->img_window, x, j++,
			get_rgba(&game->coor.t_ceiling));
	ft_draw_textured_wall(game, x, top, bottom);
	j = bottom;
	while (j < WIN_HEIGHT)
		mlx_put_pixel(game->img_window, x, j++, get_rgba(&game->coor.t_floor));
}

void	put_textures(void *param)
{
	t_cub	*game;
	int		i;
	int		top;
	int		bottom;

	game = (t_cub *) param;
	ft_raycasting(game);
	mlx_delete_image(game->init, game->img_window);
	game->img_window = mlx_new_image(game->init, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(game->init, game->img_window, 0, 0);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ft_calculate_wall_dimensions(game, i, &top, &bottom);
		ft_draw_walls_and_floor(game, i, top, bottom);
		i++;
	}
}
