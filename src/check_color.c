/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:22 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/11 16:44:26 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_digit(char *color)												// Función para verificar si una cadena es un número válido o contiene caracteres no permitidos
{
	if (ft_is_whitespace_only(color))											// Si la cadena es solo espacios en blanco, retorna error (1).
		return (1);
	while (color && *color)														// Recorre la cadena carácter por carácter.
	{
		if (!ft_isspace(*color) && !ft_isdigit(*color))							// Si encuentra un carácter que no es espacio ni número, retorna error.
			return (1);
		color++;																// Avanza al siguiente carácter.
	}
	return (0);																	// Si solo hay espacios y dígitos, es válido.
}

void	ft_check_color(t_cub *game, char *line, t_color *color)					// Función para validar y guardar un color RGB
{
	char	**rgb;
	int		i;
	int		error;
	long	result;
	
	i = 0;
	error = (line == NULL);														// Si la línea es NULL, marca error.
	if (error || ft_strnstr(line, ",,", ft_strlen(line)))						// Verifica si hay comas seguidas (,,) o línea vacía.
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
	rgb = ft_split(line, ',');													// Separa la línea en partes usando ',' como delimitador.
	while (rgb && rgb[i] && !error)												// Mientras haya valores y no haya error.
	{
		result = ft_atol(rgb[i]);												// Convierte la cadena en un número.
		if (check_digit(rgb[i]) || result < 0 || result > 255)					// Verifica si es un número válido entre 0 y 255.
			error = 1;
		else if(i == 0)															// Asigna el primer valor al rojo.
			color->r = result;
		else if(i == 1)															// Asigna el segundo valor al verde.
			color->g = result;
		else if(i == 2)															// Asigna el tercer valor al azul.
			color->b = result;
		else if(i > 2)															// Si hay más de 3 valores, marca error.
			error = 1;
		i++;
	}
	free_array(rgb);															// Libera la memoria del array de valores RGB.
	if (error)																	// Si hubo un error en la validación, lanza error.
		ft_error(game, 1, "Invalid RGB value (must be 0-255)");
}