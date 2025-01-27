/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:19:25 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/27 18:44:29 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *msg)				// Imprime un mensaje de error en la salida estándar de error y termina el programa.
{
	write (2, msg, ft_strlen(msg));		// Utiliza ft_strlen para calcular la longitud del mensaje.
	write (2, "\n", 1);					// El salto de línea asegura que el mensaje termine correctamente.
	exit (EXIT_FAILURE);				// EXIT_FAILURE es un macro que indica una salida con error.
}
