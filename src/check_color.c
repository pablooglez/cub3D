/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:22 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/27 13:08:35 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_digit(char *color)
{
	if (ft_is_whitespace_only(color))
		return (1);
	while (color && *color)
	{
		if (!ft_isspace(*color) && !ft_isdigit(*color))
			return (1);
		color++;
	}
	return (0);
}

static int	validate_rgb_value(char *value)
{
	long	result;

	result = ft_atol(value);
	if (check_digit(value) || result < 0 || result > 255)
		return (1);
	return (0);
}

static void	assign_rgb_value(t_color *color, char *value, int index)
{
	long	result;

	result = ft_atol(value);
	if (index == 0)
		color->r = result;
	else if (index == 1)
		color->g = result;
	else if (index == 2)
		color->b = result;
}

void	ft_check_color(t_cub *game, char *line, t_color *color)
{
	char	**rgb;
	int		i;
	int		error;

	i = 0;
	error = (line == NULL);
	if (error || ft_strnstr(line, ",,", ft_strlen(line)))
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
	rgb = ft_split(line, ',');
	while (rgb && rgb[i] && !error)
	{
		if (validate_rgb_value(rgb[i]))
			error = 1;
		else
			assign_rgb_value(color, rgb[i], i);
		if (i > 2)
			error = 1;
		i++;
	}
	if (i != 3)
		error = 1;
	free_array(rgb);
	if (error)
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
}
