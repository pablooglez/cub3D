/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:32:59 by albelope          #+#    #+#             */
/*   Updated: 2025/02/19 13:10:46 by albelope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Docs: file:///home/albelope/Desktop/cub3d/docs_md/raycasting/ft_init_ray.md
void	ft_init_ray(t_cub *game, int x, double ray_angle)
{
	t_ray	*ray;

	ray = &game->rays[x];
	ray->ray_angle = ray_angle;
	ray->delta_x = cos(ray_angle);
	ray->delta_y = sin(ray_angle);
	ray->map_x = (int)floor(game->player->x);											// Ver la posibilidad de que sea round o float kasting
	ray->map_y = (int)floor(game->player->y);											// para mas precision y flujo del movimiento y porgrama
	if (ray->delta_x == 0)												// para manejar si el rayo es solo vertical(solo se mueve en Y)
		ray->delta_dist_x = 1e30;										//1e30 es abrev de 1 x 30 ceros 1x10 al cubo // evita division por 0
	else
		ray->delta_dist_x = fabs(1 / ray->delta_x);						//fabs devuelve el valor absoluto de un DOUBLE, incluido en la math.h podemos usarla!
	if (ray->delta_y == 0)
		ray->delta_dist_y = 1e30;
	else																// this bucleses, los usamos para evitar cuando los rayos sean totalmente horizontal o vertical
		ray->delta_dist_y = fabs(1 / ray->delta_y);						// se asigna valor muy grande(1e30) para garantizar que nunca cruzara X o Y(segun)
}																		// y evitar la division por 0, para que no se bloquee el programa.

// Docs: file:///home/albelope/Desktop/cub3d/docs_md/raycasting/ft_calculate_ray_direction_and_step.md
void	ft_calculate_ray_direction_and_steps(t_cub *game, int x)
{
	t_ray	*ray;

	ray = &game->rays[x];												// obtenemos la direccion del rayo en la columna x
	if (ray->delta_x < 0)												// si se mueve hacia la izquierda en x
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else																// si se mueve hacia la derecha en X
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;	
	}
	if (ray->delta_y < 0)												// si se mueve hacia arriba en Y
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else																// si se mueve hacia abajo en Y
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;	
	}
}

// DOCS file:///home/albelope/Desktop/cub3d/docs_md/raycasting/ft_dda_algorithm.md
void	ft_dda_algorithm(t_cub *game, int x)
{
	t_ray	*ray;
 
	ray = &game->rays[x];
	while (1)															// bucle activo para encontrar una pared
	{
		if (ray->side_dist_x < ray->side_dist_y)						// Si el borde en x esta mas cerca
		{
			ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x; 	// incrementar distancia en x
			ray->map_x = ray->map_x + ray->step_x;						// avanza una celda en x
			if(ray->step_x == 1)
				ray->side = EAST;										// si se mueve hacia la izquierda o derecha se marca
			else														// los lados impactados
				ray->side = WEST;
		}
		else															// Si el borde en y esta mas cerca
		{
			ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;	// incrementar distancia en y
			ray->map_y = ray->map_y + ray->step_y;						// avanza una celda en y
			if (ray->step_y == -1)
				ray->side = SOUTH;
			else														//aqui easy de quitar dos lineas sin bucles para norminette
				ray->side = NORTH;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')					// si estamos en una pared sale del bucle
			break ;
	}
}

// DOCS file:///home/albelope/Desktop/cub3d/docs_md/raycasting/ft_get_perspective_hit_distance.md
void	ft_get_perspective_hit_distance(t_cub *game, int x)
{
	t_ray	*ray;

	ray = &game->rays[x];
	if (ray->side == EAST || ray->side == WEST)
		ray->perpection_distance = (ray->map_x - game->player->x
				+ (1 - ray->step_x) / 2) / ray->delta_x;
	else
		ray->perpection_distance = (ray->map_y - game->player->y
				+ (1 - ray->step_y) / 2) / ray->delta_y;
	ray->perpection_distance = ray->perpection_distance * cos(ray->ray_angle
			- game->player->view);
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
