/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:32:59 by albelope          #+#    #+#             */
/*   Updated: 2025/02/24 22:11:02 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_ray(t_cub *game, int x, double ray_angle)
{
	t_ray	*ray;

	ray = &game->rays[x];
	ray->ray_angle = ray_angle;
	ray->delta_x = cos(ray_angle);
	ray->delta_y = sin(ray_angle);
	ray->map_x = (int)floor(game->player->x);
	ray->map_y = (int)floor(game->player->y);
	if (ray->delta_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->delta_x);
	if (ray->delta_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->delta_y);
}

void	ft_calculate_ray_direction_and_steps(t_cub *game, int x)
{
	t_ray	*ray;

	ray = &game->rays[x];
	if (ray->delta_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->delta_dist_x;
	}
	if (ray->delta_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->delta_dist_y;
	}
}

void	ft_get_perspective_hit_distance(t_cub *game, int x)
{
	t_ray	*ray;
	double	angle_diff;

	ray = &game->rays[x];
	if (ray->side == EAST || ray->side == WEST)
		ray->perpection_distance = (ray->map_x - game->player->x
				+ (1 - ray->step_x) / 2) / ray->delta_x;
	else
		ray->perpection_distance = (ray->map_y - game->player->y
				+ (1 - ray->step_y) / 2) / ray->delta_y;
	if (ray->side == EAST || ray->side == WEST)
	{
		ray->hit_x = ray->map_x;
		ray->hit_y = game->player->y + ray->perpection_distance * ray->delta_y;
	}
	else
	{
		ray->hit_y = ray->map_y;
		ray->hit_x = game->player->x + ray->perpection_distance * ray->delta_x;
	}
	angle_diff = ray->ray_angle - game->player->view;
	ray->perpection_distance *= cos(angle_diff);
	if (ray->perpection_distance < 0.01)
		ray->perpection_distance = 0.01;
}

void	ft_raycasting(t_cub *game)
{
	int		x;
	double	ray_angle;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_angle = (game->player->view - (FOV / 2.0)) + (((double)x)
				/ WIN_WIDTH) * FOV;
		ft_init_ray(game, x, ray_angle);
		ft_calculate_ray_direction_and_steps(game, x);
		ft_dda_algorithm(game, x);
		ft_get_perspective_hit_distance(game, x);
		x = x + 1;
	}
}
