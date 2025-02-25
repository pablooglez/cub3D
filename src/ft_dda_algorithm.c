/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:10:34 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/24 22:12:39 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	update_ray_distances(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		if (ray->step_x == 1)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		if (ray->step_y == -1)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
}

void	ft_dda_algorithm(t_cub *game, int x)
{
	t_ray	*ray;

	ray = &game->rays[x];
	while (1)
	{
		update_ray_distances(ray);
		if (game->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}
