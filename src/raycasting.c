/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:46:33 by albelope          #+#    #+#             */
/*   Updated: 2025/02/05 13:05:56 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define NUM_RAYS WIN_WIDTH
#define RAY_STEP 0.1f
#define MAX_DISTANCE 20.0f
#define M_PI 3.14159265358979323846

static int	is_hit_wall(char **map, float x, float y)
{
	if (map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

static float	find_wall_hit(t_cub *game, float ray_angle, int *hit_vertical)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;
	float	distance;

	x = game->player->x;
	y = game->player->y;
	step_x = cos(ray_angle) * RAY_STEP;
	step_y = sin(ray_angle) * RAY_STEP;
	distance = 0.0f;
	while (!is_hit_wall(game->map, x, y) && distance < MAX_DISTANCE)
	{
		x += step_x;
		y += step_y;
		distance += RAY_STEP;
	}
	*hit_vertical = (fabs(x - (int)x) < fabs(y - (int)y));
	return (distance);
}

static mlx_texture_t	*get_texture(t_cub *game, int x)
{
	if (game->rays[x].hit_vertical)
	{
		if (game->rays[x].ray_dir_x > 0)
			return (game->coor->txt_east_i);
		return (game->coor->txt_west_i);
	}
	if (game->rays[x].ray_dir_y > 0)
		return (game->coor->txt_south_i);
	return (game->coor->txt_north_i);
}

static void	draw_texture(t_cub *game, int x, int y, uint32_t color)
{
	if (y >= 0 && y < WIN_HEIGHT)
		mlx_put_pixel(game->img_window, x, y, color);
}

static void	get_wall_limits(int wall_height, int *draw_start, int *draw_end)
{
	*draw_start = (WIN_HEIGHT / 2) - (wall_height / 2);
	*draw_end = (WIN_HEIGHT / 2) + (wall_height / 2);
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

static uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)texture->height)
		tex_y = texture->height - 1;
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

static void	draw_vertical_line(t_cub *game, int x, int wall_height)
{
	int				y;
	int				tex_x;
	int				tex_y;
	int				draw_start;
	int				draw_end;
	mlx_texture_t	*texture;
	uint32_t		color;

	texture = get_texture(game, x);
	if (!texture)
		return ;
	get_wall_limits(wall_height, &draw_start, &draw_end);
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = ((y - draw_start) * texture->height) / wall_height;
		tex_x = ((int)(game->rays[x].wall_hit_x * texture->width) 
			+ (int)(game->rays[x].wall_hit_y * texture->width)) % (int)texture->width;
		color = get_texture_color(texture, tex_x, tex_y);
		draw_texture(game, x, y, color);
		y++;
	}
}




void	cast_rays(void *param)
{
	t_cub	*game;
	int		i;
	float	ray_angle;
	float	step_angle;
	int		wall_height;
	int		hit_vertical;

	game = (t_cub *)param;
	step_angle = (FOV * (M_PI / 180)) / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = game->player->view - ((FOV * (M_PI / 180)) / 2) + (i * step_angle);
		game->rays[i].ray_angle = ray_angle;
		game->rays[i].ray_dir_x = cos(ray_angle);
		game->rays[i].ray_dir_y = sin(ray_angle);
		game->rays[i].distance = find_wall_hit(game, ray_angle, &hit_vertical);
		game->rays[i].hit_vertical = hit_vertical;
		game->rays[i].wall_hit_x = game->player->x + game->rays[i].ray_dir_x * game->rays[i].distance;
		game->rays[i].wall_hit_y = game->player->y + game->rays[i].ray_dir_y * game->rays[i].distance;
		wall_height = (int)(WIN_HEIGHT / (game->rays[i].distance + 0.0001));
		draw_vertical_line(game, i, wall_height);
		i++;
	}
}
