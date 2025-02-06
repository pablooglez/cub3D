/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:22 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/06 21:10:28 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int check_digit(char *color)
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

void	ft_check_color(t_cub *game, char *line, t_color *color)
{
	char **rgb;
	int		i;
	int		error;
	long	result;
	
	i = 0;
	error = (line == NULL);
	if (error || ft_strnstr(line, ",,", ft_strlen(line)))
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
	rgb = ft_split(line, ',');
	while (rgb && rgb[i] && !error)
	{
		result = ft_atol(rgb[i]);
		if (check_digit(rgb[i]) || result < 0 || result > 255)
			error = 1;
		else if(i == 0)
			color->r = result;
		else if(i == 1)
			color->g = result;
		else if(i == 2)
			color->b = result;
		else if(i > 2)
			error = 1;
		i++;
	}
	free_array(rgb);
	if (error)
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
}