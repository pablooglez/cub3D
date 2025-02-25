/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:23:58 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/24 22:13:32 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>						// read, write y close
# include <stdio.h>							// printf
# include <stdlib.h>						// malloc, free
# include <string.h>						//strerror
# include <errno.h>							// perror
# include <fcntl.h>							// open
# include <sys/time.h>						// gettimeofday
# include <math.h>							// sin, cos, tan, sqrt, pow ...
# include "../Libft/libft.h"				// Libft
# include "../Libft/get_next_line_bonus.h"	//Get_next_line
# include "../MLX42/include/MLX42/MLX42.h"	// MLX42

# define WIN_WIDTH 1940
# define WIN_HEIGHT 1280
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923
# define FOV 1.04719755119659774615			//((60 * M_PI) / 180)
# define WALL_SIZE 1.0 

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	float	x;
	float	y;
	float	view;
	float	move_speed;
	float	rot_speed;
}	t_player;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

enum e_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_ray
{
	double			ray_angle;
	double			delta_x;
	double			delta_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perpection_distance;
	double			distance;
	double			side_dist_x;
	double			side_dist_y;
	double			hit_x;
	double			hit_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
}	t_ray;

typedef struct s_coor
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	char			*torch;
	int				n_coor;
	t_color			t_floor;
	t_color			t_ceiling;
	mlx_texture_t	*txt_north_i;
	mlx_texture_t	*txt_south_i;
	mlx_texture_t	*txt_west_i;
	mlx_texture_t	*txt_east_i;
}	t_coor;

typedef struct s_wall_data
{
	int				x;
	int				start;
	int				end;
	int				height;
}	t_wall_data;

typedef struct s_texture_data
{
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				tex_x;
	double			step;
	double			tex_pos;
}	t_texture_data;

typedef struct s_cub
{
	mlx_t			*init;
	mlx_image_t		*img_window;
	int				fd;
	char			*map[1024];
	int				map_len;
	int				error_flag;
	int				start_map;
	int				n_player;
	t_player		*player;
	t_coor			coor;
	t_ray			rays[WIN_WIDTH];
	t_keys			keys;
	void			*mlx_data;
}	t_cub;

//----------------CHECK_COLOR--------------------//
void			ft_check_color(t_cub *game, char *line, t_color *color);

//----------------CHECK_FILE--------------------//
void			ft_check_file(t_cub *game, char *str);

//----------------CHECK_MAP--------------------//
void			fill_map_with_spaces(t_cub *game);
void			ft_check_map(t_cub *game, int y, int x);

//----------------CREATE_GAME--------------------//
void			load_textures(t_cub *game);
void			ft_mlx_init(t_cub *game);

//----------------ERROR---------------------//
void			ft_print_error(const char *msg);
void			ft_error(t_cub *game, int use, const char *msg);

//----------------FREE----------------------//
void			free_textures(t_coor *coor);
void			free_coor(t_coor *coor);
void			free_array(char **array);
void			free_game(t_cub *game);

//----------------FT_DDA_ALGORITHM-----------------------//
void			ft_dda_algorithm(t_cub *game, int x);

//------------------INIT_AND_MEMORY---------------------//
void			ft_init_game(t_cub *game);
void			init_image(t_cub *game);
void			init_wall_data(t_wall_data *wall, t_cub *game, int x);
t_texture_data	init_texture_data(t_cub *game, t_wall_data wall);

//----------------MAP-----------------------//
void			ft_get_map(t_cub *game);

//----------------MOVING--------------------//
void			ft_process_movement(void *param);
void			ft_keymoves(mlx_key_data_t keydata, void *param);

//----------------PLAYER_POSITION--------------------//
void			initialize_player_position(t_cub *game);

//----------------RAYCASTING---------------------//
void			ft_init_ray(t_cub *game, int x, double ray_angle);
void			ft_calculate_ray_direction_and_steps(t_cub *game, int x);
void			ft_get_perspective_hit_distance(t_cub *game, int x);
void			ft_raycasting(t_cub *game);

//----------------TEXTURES---------------------//
mlx_texture_t	*ft_select_texture(t_cub *game, int side);
int				ft_get_texture_x(t_ray *ray, mlx_texture_t *texture);
void			put_textures(void *param);

//----------------UTILS---------------------//
void			change_spaces(t_cub *game);
int				ft_find_char_index(char *s);
int				ft_is_whitespace_only(char *line);
unsigned int	get_rgba(t_color *color);

#endif