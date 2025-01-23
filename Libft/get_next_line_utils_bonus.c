/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:32:40 by pablogon          #+#    #+#             */
/*   Updated: 2024/08/28 18:06:37 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ftg_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ftg_strdup(const char *s1)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ftg_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ftg_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	m_len;
	unsigned int	i;

	i = 0;
	if (start > ftg_strlen(s))
		m_len = 0;
	else
		m_len = ftg_strlen(s) - start;
	if (len > m_len)
		len = m_len;
	len += 1;
	str = (char *)malloc(len);
	if (str == NULL)
		return (NULL);
	while (s[i] && --len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_freestorage(char **storage)
{
	free(*storage);
	*storage = NULL;
	return (NULL);
}

char	*ft_readifdonthavenewline(char *storage, int fd)
{
	int		bytesread;
	char	buffer[BUFFER_SIZE + 1];
	char	*new;

	while (ft_searchnewline(storage) == -1)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (ft_freestorage(&storage));
		buffer[bytesread] = '\0';
		if (buffer[0] == '\0')
		{
			if (storage[0] == '\0')
				return (ft_freestorage(&storage));
			return (storage);
		}
		new = ftg_strjoin(storage, buffer);
		if (!new)
			return (ft_freestorage(&storage));
		free (storage);
		storage = new;
	}
	return (storage);
}
