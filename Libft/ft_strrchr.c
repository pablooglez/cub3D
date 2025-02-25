/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:53:24 by pablogon          #+#    #+#             */
/*   Updated: 2025/02/24 21:50:13 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char		*last;
	int			i;

	last = NULL;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			last = (char *)&str[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (last);
}
