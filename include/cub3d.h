/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:23:58 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/03 21:12:06 by pablogon         ###   ########.fr       */
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


# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FOV 60
# define WALL_SIZE 640 

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
}	t_player;

typedef struct s_coor
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	int				n_coor;
	t_color			*t_floor;
	t_color			*t_ceiling;
	mlx_texture_t	*txt_north_i;
	mlx_texture_t	*txt_south_i;
	mlx_texture_t	*txt_west_i;
	mlx_texture_t	*txt_east_i;
}	t_coor;

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
	t_coor			*coor;
}	t_cub;

//----------------CHECK_FILE--------------------//
void	ft_check_file(t_cub *game, char *str);

//----------------CHECK_MAP--------------------//
void	ft_check_map(t_cub *game, int y, int x);

//----------------CREATE_GAME--------------------//
void	ft_mlx_init(t_cub *game);

//----------------ERROR---------------------//
void	ft_print_error(const char *msg);
void	ft_error(t_cub *game, int use, const char *msg);

//----------------FREE----------------------//
void	free_textures(t_coor *coor);
void	free_coor(t_coor *coor);
void	free_array(char **array);
void	free_game(t_cub *game);

//----------------MAP-----------------------//

void	ft_get_map(t_cub *game, char *aux, char *result);

//----------------UTILS---------------------//
void	change_spaces(t_cub *game);
int		ft_find_char_index(char *s, int c);
int		ft_is_whitespace_only(char *line);

//------------------UTILS2---------------------//
t_coor			*malloc_coor(t_cub *game);
void			ft_init_game(t_cub *game);
#endif